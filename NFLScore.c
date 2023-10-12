#include <stdio.h>

void findScoringCombinations(int score) {
    int td2, td1, td, fg, safety;

    for (td2 = 0; td2 * 8 <= score; td2++) {
        for (td1 = 0; td1 * 7 <= score; td1++) {
            for (td = 0; td * 6 <= score; td++) {
                for (fg = 0; fg * 3 <= score; fg++) {
                    for (safety = 0; safety * 2 <= score; safety++) {
                        if (td2 * 8 + td1 * 7 + td * 6 + fg * 3 + safety * 2 == score) {
                            printf("%d TD + 2pt, %d TD + FG, %d TD, %d 3pt FG, %d Safety\n", td2, td1, td, fg, safety);
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int score;

    while (1) {
        printf("Enter 0 or 1 to STOP\n");
        printf("Enter the NFL score: ");
        scanf("%d", &score);

        if (score <= 1) {
            break;
        }

        printf("Possible combinations of scoring plays:\n");
        findScoringCombinations(score);
    }

    return 0;
}
