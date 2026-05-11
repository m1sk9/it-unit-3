#include <stdio.h>
#include <string.h>

int main(void) {
    int line_no = 1;
    int col_no = 0;
    char line[61] = {0};

    while (col_no < 10) {
        col_no++;
        char cell[8];
        snprintf(cell, sizeof(cell), "%6d", line_no * col_no);
        memcpy(line + 6 * (col_no - 1), cell, 6);
    }
    line[60] = '\0';

    while (line_no < 10) {
        line_no++;
        printf("%-60s\n", line);

        for (int k = 0; k < 6 * (line_no - 1); k++) {
            line[k] = ' ';
        }

        col_no = line_no - 1;

        while (col_no < 10) {
            col_no++;
            char cell[8];
            snprintf(cell, sizeof(cell), "%6d", line_no * col_no);
            memcpy(line + 6 * (col_no - 1), cell, 6);
        }
        line[60] = '\0';
    }

    printf("%-60s\n", line);
    return 0;
}
