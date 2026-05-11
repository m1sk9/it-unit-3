/* レポート課題1-3 a: 上下逆に印字 */
#include <stdio.h>

int main(void) {
    for (int line_no = 10; line_no >= 1; line_no--) {
        char line[61] = {0};
        for (int col_no = 1; col_no <= line_no; col_no++) {
            snprintf(line + 6 * (col_no - 1), sizeof(line) - 6 * (col_no - 1), "%6d",
                     line_no * col_no);
        }
        printf("%s\n", line);
    }
    return 0;
}
