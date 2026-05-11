/*
 *  作成日: 2026/05/11
 *
 *  入力テキストファイルを 1 パスで走査し，T1/T2/T3 の構造に基づいて
 *  4 種類のカウントを計算するプログラム
 *    T1: 1 文字目が '1' の行
 *    T2: 1 文字目が '2' の行
 *    T3: 1 文字目が '3' の行
 */

#include <stdio.h>

int main(int argc, char *argv[]) {
  // ファイルの処理
  FILE *file;
  char buffer[256];
  int type = 0;
  int countA = 0;
  int countB = 0;
  int countC = 0;
  int countD = 0;

  if (argc < 2) {
    fprintf(stderr, "Usage: %s <input file>\n", argv[0]);
    return 1;
  }

  // ファイルをオープン
  file = fopen(argv[1], "r");
  if (file == NULL) {
    fprintf(stderr, "Cannot open file: %s\n", argv[1]);
    return 1;
  }

  // 最初の先読み
  fgets(buffer, sizeof(buffer), file);
  sscanf(buffer, "%d", &type);

  // 前置き部の処理
  while (type != 1) {
    // T1以外の処理
    countA++;
    fgets(buffer, sizeof(buffer), file);
    sscanf(buffer, "%d", &type);
  }

  // 最初のT1の処理
  printf("%s", buffer); // 最初のT1を表示
  fgets(buffer, sizeof(buffer), file);
  sscanf(buffer, "%d", &type);

  // バッチ群の処理
  while (type != 2) {
    // バッチの処理
    if (type == 1) {
      // T1バッチの処理
      while (type == 1) {
        // T1行の処理
        countC++;
        fgets(buffer, sizeof(buffer), file);
        sscanf(buffer, "%d", &type);
      }
    } else if (type == 3) {
      // T3バッチの処理
      while (type == 3) {
        // T3行の処理
        fgets(buffer, sizeof(buffer), file);
        sscanf(buffer, "%d", &type);
      }
      countD++;
    }
    countB++;
  }

  // 最後のT2の処理
  printf("%s", buffer); // 最後の行を表示
  printf("A: %d B: %d C: %d D: %d\n", countA, countB, countC, countD);

  // ファイルをクローズ
  fclose(file);
  return 0;
}
