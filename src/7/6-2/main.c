#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 課題6-2 プログラム12-1 ── 電報の解析（境界不一致）
 *   P1 と P2 を中間ファイル経由で連結し，main から
 *   「電報を解析する: seq P1; P2; end」の構造で順に実行する．
 *     P1 : 入力ファイル → 中間ファイル（単語列）
 *     P2 : 中間ファイル → 報告書（標準出力）
 *   入力は整形済みとする（最後に空電報 ZZZZ が一つだけ現れる）．
 */

#define MAXLINE 110 /* 各行は改行を除き100文字以下 */
#define MAXWORD 110
#define INTERMEDIATE "intermediate.txt"

/* ========== P1：入力側（行ごとに実行，電報のことは知らない） ========== */
void P1(const char *infile) {
    FILE *fmid;
    FILE *fin;
    char line[MAXLINE + 2] = {0};
    char word[MAXWORD + 1] = {0};
    int i;
    int j;
    int size;
    char *r;

    fmid = fopen(INTERMEDIATE, "w"); /* 中間ファイルのオープン */
    fin = fopen(infile, "r");        /* 入力ファイルのオープン */
    if (fmid == NULL || fin == NULL) {
        fprintf(stderr, "P1: ファイルを開けません\n");
        exit(1);
    }

    r = fgets(line, sizeof(line), fin); /* 先読み（最初の行） */

    while (r != NULL) { /* 行の処理: iter until eof */
        i = 0;
        while (line[i] != '\n' && line[i] != '\0') { /* 文字列の処理: iter */
            if (line[i] == ' ') {                    /*   select 空白列 */
                while (line[i] == ' ') {             /*     空白列の処理: iter while */
                    i++;
                }
            } else { /*   or 単語 */
                j = 0;
                size = 0; /*     単語の処理: seq */
                while (line[i] != ' ' && line[i] != '\n' && line[i] != '\0') {
                    word[j++] = line[i++]; /*       単語の読込み: iter */
                    size++;
                }
                word[j] = '\0';
                fprintf(fmid, "%d %s\n", size, word); /*       write size, word */
            }
        }
        r = fgets(line, sizeof(line), fin); /* 次の行を先読み */
    }

    fclose(fin);  /* 入力ファイルのクローズ */
    fclose(fmid); /* 中間ファイルのクローズ */
}

/* ========== P2：出力側（電報ごとに実行，行のことは知らない） ========== */
void P2(void) {
    FILE *fmid;
    char word[MAXWORD + 1] = {0};
    int size;
    int telno;
    int wdcount;
    int oscount;

    fmid = fopen(INTERMEDIATE, "r"); /* 中間ファイルのオープン */
    if (fmid == NULL) {
        fprintf(stderr, "P2: 中間ファイルを開けません\n");
        exit(1);
    }

    (void)fscanf(fmid, "%d %110s", &size, word); /* 先読み（最初の単語） */
    printf("Telegram Analysis\n");               /* 見出し部の処理 */
    telno = 1;

    while (strcmp(word, "ZZZZ") != 0) { /* 報告書本体の処理: iter until ZZZZ */
        printf("Telegram %d\n", telno); /*   1行目の処理 */
        wdcount = 0;
        oscount = 0;
        while (strcmp(word, "ZZZZ") != 0) { /*   電報本体の処理: iter until ZZZZ */
            if (size < 13) {                /*     単語の処理: select */
                wdcount++;                  /*       正常語の処理 */
            } else {
                wdcount++;
                oscount++; /*       異常語の処理 */
            }
            (void)fscanf(fmid, "%d %110s", &size, word); /*     次の単語を読込み */
        }
        printf("%d words of which %d oversize\n", wdcount, oscount); /*   2行目の処理 */
        (void)fscanf(fmid, "%d %110s", &size, word); /*   次の電報の先頭語を読込み */
        telno++;
    }

    printf("End Analysis\n"); /* 終了部の処理 */
    fclose(fmid);             /* 中間ファイルのクローズ */
}

/* ========== main：電報を解析する: seq P1; P2; end ========== */
int main(int argc, char *argv[]) {
    const char *infile = (argc > 1) ? argv[1] : "telegram_input.txt";
    P1(infile);
    P2();
    return 0;
}
