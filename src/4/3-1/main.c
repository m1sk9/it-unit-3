#include <stdio.h>

int main(void) {
    FILE *pf = fopen("pf.txt", "r");
    FILE *epf = fopen("epf.txt", "w");

    if (!pf || !epf) {
        perror("fopen");
        return 1;
    }

    char buf[256];
    char date[32];
    int nextCusNo;
    int cusNo;
    int amount;
    int cusAmount;
    int totalAmount;

    /* EPF の作成 */
    totalAmount = 0;
    if (!fgets(buf, sizeof(buf), pf)) {
        nextCusNo = 0;
    } else {
        sscanf(buf, "%d%s%d", &nextCusNo, date, &amount);
    }

    /**
     * EPF 本体の処理
     *  : iter until PFの終わり
     */
    while (nextCusNo != 0) {
        /* 顧客グループの処理 */
        cusNo = nextCusNo;
        cusAmount = 0;

        /**
         * 顧客グループ本体の処理
         * :  iter until PFの終わり または cusNo != nextCusNo
         */
        while (nextCusNo == cusNo) { // EoF の場合は nextCusNo = 0 なので自動で抜ける

            /* 支払行の処理 */
            fprintf(epf, "%s", buf);
            cusAmount += amount;

            if (!fgets(buf, sizeof(buf), pf)) {
                nextCusNo = 0;
            } else {
                sscanf(buf, "%d%s%d", &nextCusNo, date, &amount);
            }
        }

        /* 顧客別支払総額の処理 */
        fprintf(epf, "顧客別総額: %d %d\n", cusNo, cusAmount);
        totalAmount += cusAmount;
    }

    fprintf(epf, "総額 %d\n", totalAmount);
    fclose(pf);
    fclose(epf);
    return 0;
}
