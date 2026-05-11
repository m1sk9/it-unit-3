#include <stdio.h>

int main(void) {
  int line_no = 1;
  int col_no = 0;
  char line[61] = {0};

  while (col_no < 10) {
    col_no++;
    snprintf(line + 6 * (col_no - 1), sizeof(line) - 6 * (col_no - 1), "%6d",
             line_no * col_no);
  }

  while (line_no < 10) {
    line_no++;
    col_no = 0;
    printf("%-60s\n", line);

    while (col_no < 10) {
      col_no++;
      snprintf(line + 6 * (col_no - 1), sizeof(line) - 6 * (col_no - 1), "%6d",
               line_no * col_no);
    }
  }

  printf("%-60s\n", line);
  return 0;
}
