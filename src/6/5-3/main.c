#include <stdio.h>
#include <stdlib.h>

#define MAX_JOB 1000 /* ジョブIDは3桁，最大999 */
#define LINE_LEN 256 /* 1レコードは256バイト以下 */

/* 時刻 HH:MM:SS を秒に変換（ジョブ・プログラムは午前0時をまたがない） */
static int to_sec(int h, int m, int s) {
    return h * 3600 + m * 60 + s;
}

/* ============================================================
   unmerge : ログファイルを読み，各レコードをジョブIDごとの
             ジョブファイルへ振り分ける
   ============================================================ */
static void unmerge(const char *logname) {
    FILE *log = fopen(logname, "r");
    if (!log) {
        perror(logname);
        exit(1);
    }

    FILE *job_fp[MAX_JOB] = {NULL}; /* ジョブIDとファイルポインタの対応 */
    char line[LINE_LEN];

    /* レコードの処理*（1レコードずつ振り分け） */
    while (fgets(line, sizeof(line), log)) {
        char code;
        int job_id;
        if (sscanf(line, " %c %d", &code, &job_id) != 2)
            continue;
        if (job_id < 0 || job_id >= MAX_JOB)
            continue;

        /* 対応するジョブファイルがなければ生成して開く */
        if (!job_fp[job_id]) {
            char fname[LINE_LEN];
            sprintf(fname, "J%03d.txt", job_id);
            job_fp[job_id] = fopen(fname, "w");
            if (!job_fp[job_id]) {
                perror(fname);
                exit(1);
            }
        }
        /* 対応するジョブファイルへレコードを出力 */
        fputs(line, job_fp[job_id]);
    }

    /* すべてのジョブファイルをクローズ */
    for (int i = 0; i < MAX_JOB; i++)
        if (job_fp[i])
            fclose(job_fp[i]);
    fclose(log);
}

/* ============================================================
   summarize : 各ジョブファイルを読み，ジョブ時間・プログラム数・
               総プログラム時間を求めてサマリファイルへ1行出力
   ============================================================ */
static void summarize(const char *sumname) {
    FILE *sum = fopen(sumname, "w");
    if (!sum) {
        perror(sumname);
        exit(1);
    }

    /* ジョブファイル（ジョブ情報）の処理*（ジョブIDの昇順） */
    for (int id = 0; id < MAX_JOB; id++) {
        char fname[LINE_LEN];
        sprintf(fname, "J%03d.txt", id);
        FILE *job = fopen(fname, "r");
        if (!job)
            continue; /* そのIDのジョブファイルは存在しない */

        char line[LINE_LEN];
        int n_sec = 0, f_sec = 0, l_sec = 0;
        int prog_count = 0; /* プログラム数の初期化 */
        int total_prog = 0; /* 総プログラム時間の初期化 */

        while (fgets(line, sizeof(line), job)) {
            char code;
            int job_id, prog_id, h, m, s;
            sscanf(line, " %c", &code);

            if (code == 'N') { /* Nの処理 */
                sscanf(line, " %c %d %d:%d:%d", &code, &job_id, &h, &m, &s);
                n_sec = to_sec(h, m, s);
            } else if (code == 'F') { /* Fの処理 */
                sscanf(line, " %c %d %d:%d:%d", &code, &job_id, &h, &m, &s);
                f_sec = to_sec(h, m, s);
            } else if (code == 'L') { /* Lの処理（プログラムの処理*） */
                sscanf(line, " %c %d %d %d:%d:%d", &code, &job_id, &prog_id, &h, &m, &s);
                l_sec = to_sec(h, m, s);
            } else if (code == 'U') { /* Uの処理（プログラムの処理*） */
                sscanf(line, " %c %d %d %d:%d:%d", &code, &job_id, &prog_id, &h, &m, &s);
                int u_sec = to_sec(h, m, s);
                prog_count++;                /* プログラム数++ */
                total_prog += u_sec - l_sec; /* 総プログラム時間に加算 */
            }
        }
        int job_time = f_sec - n_sec; /* ジョブ時間算出 */

        /* ジョブ時間・プログラム数・総プログラム時間をサマリへ出力 */
        fprintf(sum, "%d %d %d\n", job_time, prog_count, total_prog);
        fclose(job);
    }
    fclose(sum);
}

/* ============================================================
   report : サマリファイルを集計し，報告書を出力する
   ============================================================ */
static void report(const char *sumname, const char *repname) {
    FILE *sum = fopen(sumname, "r");
    if (!sum) {
        perror(sumname);
        exit(1);
    }
    FILE *rep = fopen(repname, "w");
    if (!rep) {
        perror(repname);
        exit(1);
    }

    /* ジョブ数・総ジョブ時間・総プログラム数・総プログラム時間の初期化 */
    int n_jobs = 0, total_job = 0;
    int n_prog = 0, total_prog = 0;
    int jt, pc, tp;

    /* ジョブ情報の処理*（サマリ1行＝1ジョブ） */
    while (fscanf(sum, "%d %d %d", &jt, &pc, &tp) == 3) {
        n_jobs++;        /* ジョブ数++ */
        total_job += jt; /* ジョブ時間を抽出して加算 */
        n_prog += pc;
        total_prog += tp;
    }

    /* 見出し部出力 */
    fprintf(rep, "System Usage Report\n");
    /* ジョブ情報出力（平均時間 = 総ジョブ時間 / ジョブ数） */
    fprintf(rep, "Number Of Jobs = %d Average Time = %d(sec.)\n", n_jobs,
            n_jobs ? total_job / n_jobs : 0);
    /* プログラム情報出力（平均時間 = 総プログラム時間 / 総プログラム数） */
    fprintf(rep, "Number Of Programs = %d Average Time = %d(sec.)\n", n_prog,
            n_prog ? total_prog / n_prog : 0);

    fclose(sum);
    fclose(rep);
}

/* ログ解析：unmerge → summarize → report の連接 */
int main(void) {
    unmerge("log.txt");
    summarize("sum.txt");
    report("sum.txt", "report.txt");
    return 0;
}
