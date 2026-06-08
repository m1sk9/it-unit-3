#include <stdio.h>
#include <string.h>

/* 課題6-3 プログラム12-2 ── P1（入力側，独立プログラム）
 *   入力 : 標準入力（stdin）  ← パイプで `./p1 < 入力ファイル | ./p2`
 *   出力 : 標準出力（stdout） … 単語列「size word」を1行ずつ
 *   各出力の直後に fflush(stdout) を行い，バッファ内容を確実に送り出す
 *   （P2 との並行実行のタイミングを観察できるようにするため）．
 */

#define MAXLINE 110 /* 各行は改行を除き100文字以下 */
#define MAXWORD 110

int main(void) {
    char line[MAXLINE + 2] = {0};
    char word[MAXWORD + 1] = {0};
    int i;
    int j;
    int size;
    char *r;

    r = fgets(line, sizeof(line), stdin); /* 先読み（最初の行） */

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
                printf("%d %s\n", size, word); /*       stdout へ書出し */
                fflush(stdout);                /*       バッファを確実に出力 */
            }
        }
        r = fgets(line, sizeof(line), stdin); /* 次の行を先読み */
    }

    return 0;
}
