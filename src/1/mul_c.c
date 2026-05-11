/* レポート課題1-3 c: 左下の代わりに右上半分を印字 */
#include <stdio.h>
#include <string.h>

int main(void) {
  for (int line_no = 1; line_no <= 10; line_no++) {
    char line[61];
    memset(line, ' ', sizeof(line) - 1);
    line[sizeof(line) - 1] = '\0';
    for (int col_no = line_no; col_no <= 10; col_no++) {
      char cell[8];
      snprintf(cell, sizeof(cell), "%6d", line_no * col_no);
      memcpy(line + 6 * (col_no - 1), cell, 6);
    }
    printf("%s\n", line);
  }
  return 0;
}
