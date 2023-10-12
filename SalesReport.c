#include <stdio.h>
#include <math.h>

#define NUM_MONTHS 12
char *months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

void readSales(double sales[NUM_MONTHS], FILE *inputFile) {
    for (int i = 0; i < NUM_MONTHS; i++) {
        fscanf(inputFile, "%lf", &sales[i]);
    }
}

double calculateAverage(double sales[NUM_MONTHS]) {
    double sum = 0;
    for (int i = 0; i < NUM_MONTHS; i++) {
        sum += sales[i];
    }
    return sum / NUM_MONTHS;
}

void calculateMovingAverages(double sales[NUM_MONTHS], double movingAverages[NUM_MONTHS]) {
    for (int i = 0; i < NUM_MONTHS; i++) {
        double sum = 0;
        for (int j = i; j < i + 6 && j < NUM_MONTHS; j++) {
            sum += sales[j];
        }
        movingAverages[i] = sum / fmin(6, NUM_MONTHS - i);
    }
}


void sortSalesDescending(double sales[NUM_MONTHS], int sortedIndices[NUM_MONTHS]) {
    for (int i = 0; i < NUM_MONTHS; i++) {
        sortedIndices[i] = i;
    }

    for (int i = 0; i < NUM_MONTHS - 1; i++) {
        for (int j = i + 1; j < NUM_MONTHS; j++) {
            if (sales[sortedIndices[i]] < sales[sortedIndices[j]]) {
                int temp = sortedIndices[i];
                sortedIndices[i] = sortedIndices[j];
                sortedIndices[j] = temp;
            }
        }
    }
}

int main() {
    FILE *inputFile = fopen("sales_input.txt", "r");
    if (inputFile == NULL) {
        printf("Error opening the input file.\n");
        return 1;
    }

    double sales[NUM_MONTHS];
    readSales(sales, inputFile);
    fclose(inputFile);

    double movingAverages[NUM_MONTHS];
    calculateMovingAverages(sales, movingAverages);

    printf("Monthly sales report for 2022:\n");
    printf("Month\t\tSales\n");
    for (int i = 0; i < NUM_MONTHS; i++) {
        printf("%s\t\t$%.2lf\n", months[i], sales[i]);
    }

    double min = sales[0];
    double max = sales[0];
    char minMonth;
    char maxMonth;
    double avg = calculateAverage(sales);
    
    for (int i = 0; i < NUM_MONTHS; i++) {
        if (sales[i] < min){
            min = sales[i];
            minMonth = i;
        }
        if (sales[i] > max){
            max = sales[i];
            maxMonth = i;
        }
    }


    printf("\nSales summary:\n");
    printf("Minimum sales: $%.2lf (%s)\n", min, months[minMonth]);
    printf("Maximum sales: $%.2lf (%s)\n", max, months[maxMonth]);
    printf("Average sales: $%.2lf\n\n", avg);

    printf("Six-Month Moving Averages:\n");
    printf("Month\tAverage\n");
    for (int i = 0; i < 7; i++) {
        printf("%s   -   %s\t\t$%.2lf\n", months[i], months[i+5], movingAverages[i]);
    }

    int sortedIndices[NUM_MONTHS];
    sortSalesDescending(sales, sortedIndices);

    printf("\nMonthly Sales Report (Descending Order):\n");
    printf("Month\t\tSales\n");
    for (int i = 0; i < NUM_MONTHS; i++) {
        int index = sortedIndices[i];
        printf("%s\t\t$%.2lf\n", months[index], sales[index]);
    }

    return 0;
}
