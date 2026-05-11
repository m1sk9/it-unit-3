#include <stdio.h>

int main(void) {
  int line_no = 1;
  char line[61] = {0};

  snprintf(line, sizeof(line), "%6d", 1);

  while (line_no < 10) {
    line_no++;
    int col_no = 0;

    printf("%-60s\n", line);

    while (col_no < line_no) {
      col_no++;
      snprintf(line + 6 * (col_no - 1), sizeof(line) - 6 * (col_no - 1), "%6d",
               line_no * col_no);
    }
  }

  printf("%-60s\n", line);
  return 0;
}
