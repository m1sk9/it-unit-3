#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 256
#define END_MARKER 9999

int min(int a, int b) {
    return a < b ? a : b;
}

int main(void) {
    /** 各ファイルを開く */
    FILE *bfp = fopen("baseball.txt", "r");
    FILE *tfp = fopen("theater.txt", "r");
    FILE *rfp = fopen("result.txt", "w");
    if (!bfp || !tfp || !rfp) {
        perror("fopen");
        return 1;
    }

    char bbuf[BUF_SIZE];
    char tbuf[BUF_SIZE];
    char info[BUF_SIZE];
    int bcusNo;
    int tcusNo;
    int cusNo;

    /** 野球ファイルを読み込む */
    if (!fgets(bbuf, sizeof(bbuf), bfp)) {
        bcusNo = END_MARKER;
    } else {
        sscanf(bbuf, "%d%s", &bcusNo, info);
    }

    /** 演劇ファイルを読み込む */
    if (!fgets(tbuf, sizeof(tbuf), tfp)) {
        tcusNo = END_MARKER;
    } else {
        sscanf(tbuf, "%d%s", &tcusNo, info);
    }

    cusNo = min(bcusNo, tcusNo);

    /** 報告書作成本体の処理 */
    while (cusNo < END_MARKER) {
        /* 報告行の処理: select */
        if (bcusNo == cusNo && cusNo == tcusNo) {
            /* 型1: 野球観戦と演劇鑑賞の両方に応募 */
            fprintf(rfp, "%04d 1\n", cusNo);
            if (!fgets(bbuf, sizeof(bbuf), bfp)) {
                bcusNo = END_MARKER;
            } else {
                sscanf(bbuf, "%d%s", &bcusNo, info);
            }
            if (!fgets(tbuf, sizeof(tbuf), tfp)) {
                tcusNo = END_MARKER;
            } else {
                sscanf(tbuf, "%d%s", &tcusNo, info);
            }
        } else if (bcusNo == cusNo && cusNo < tcusNo) {
            /* 型2: 野球観戦だけに応募 */
            fprintf(rfp, "%04d 2\n", cusNo);
            if (!fgets(bbuf, sizeof(bbuf), bfp)) {
                bcusNo = END_MARKER;
            } else {
                sscanf(bbuf, "%d%s", &bcusNo, info);
            }
        } else if (bcusNo > cusNo && cusNo == tcusNo) {
            /* 型3: 演劇鑑賞だけに応募 */
            fprintf(rfp, "%04d 3\n", cusNo);
            if (!fgets(tbuf, sizeof(tbuf), tfp)) {
                tcusNo = END_MARKER;
            } else {
                sscanf(tbuf, "%d%s", &tcusNo, info);
            }
        }
        cusNo = min(bcusNo, tcusNo);
    }

    /* それぞれのファイルを閉じる */
    fclose(bfp);
    fclose(tfp);
    fclose(rfp);

    return 0;
}
