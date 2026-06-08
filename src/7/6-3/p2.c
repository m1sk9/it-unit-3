#include <stdio.h>
#include <string.h>

/* 課題6-3 プログラム12-2 ── P2（出力側，独立プログラム）
 *   入力 : 標準入力（stdin）  ← P1 の出力をパイプで受け取る
 *   出力 : 標準出力（stdout） … 報告書
 *   各 printf の直後に fflush(stdout) を行い，P1 との並行実行の
 *   タイミング（入力途中で報告書が出始める様子）を観察できるようにする．
 */

#define MAXWORD 110

int main(void) {
    char word[MAXWORD + 1] = {0};
    int size;
    int telno;
    int wdcount;
    int oscount;

    (void)scanf("%d %110s", &size, word); /* 先読み（最初の単語） */
    printf("Telegram Analysis\n");
    fflush(stdout); /* 見出し部の処理 */
    telno = 1;

    while (strcmp(word, "ZZZZ") != 0) { /* 報告書本体の処理: iter until ZZZZ */
        printf("Telegram %d\n", telno);
        fflush(stdout); /*   1行目の処理 */
        wdcount = 0;
        oscount = 0;
        while (strcmp(word, "ZZZZ") != 0) { /*   電報本体の処理: iter until ZZZZ */
            if (size < 13) {                /*     単語の処理: select */
                wdcount++;                  /*       正常語の処理 */
            } else {
                wdcount++;
                oscount++; /*       異常語の処理 */
            }
            (void)scanf("%d %110s", &size, word); /*     次の単語を読込み */
        }
        printf("%d words of which %d oversize\n", wdcount, oscount);
        fflush(stdout);                       /*   2行目の処理 */
        (void)scanf("%d %110s", &size, word); /*   次の電報の先頭語を読込み */
        telno++;
    }

    printf("End Analysis\n");
    fflush(stdout); /* 終了部の処理 */
    return 0;
}
