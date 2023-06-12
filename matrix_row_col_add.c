#include <stdio.h>

#define MAX_ROWS 100
#define MAX_COLS 100

int main() {
    int matrix[MAX_ROWS][MAX_COLS];
    int rows, cols, i, j, rowSum, colSum;

    printf("Enter the number of rows for the matrix: ");
    scanf("%d", &rows);

    printf("Enter the number of columns for the matrix: ");
    scanf("%d", &cols);

    printf("Enter the elements of the matrix:\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    printf("The sum of each row:\n");
    for (i = 0; i < rows; i++) {
        rowSum = 0;
        for (j = 0; j < cols; j++) {
            rowSum += matrix[i][j];
        }
        printf("Row %d: %d\n", i+1, rowSum);
    }

    printf("The sum of each column:\n");
    for (j = 0; j < cols; j++) {
        colSum = 0;
        for (i = 0; i < rows; i++) {
            colSum += matrix[i][j];
        }
        printf("Column %d: %d\n", j+1, colSum);
    }

    return 0;
}
