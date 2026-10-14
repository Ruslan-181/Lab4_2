
#include "Func.h"
// 1. Пошук MAX та MIN вище головної діагоналі (Варіант 21)
void max_min(int** A, int n_a, int* max_a, int* min_a) {
    int first = 1;
    for (int i = 0; i < n_a; i++) {
        for (int j = i + 1; j < n_a; j++) { // Елементи вище головної діагоналі: j > i
            if (first) {
                *max_a = A[i][j];
                *min_a = A[i][j];
                first = 0;
            }
            else {
                if (A[i][j] > *max_a) *max_a = A[i][j];
                if (A[i][j] < *min_a) *min_a = A[i][j];
            }
        }
    }
}

// 2. Транспонування матриці B (повертає нову динамічну матрицю m_b x n_b)
int** transpose_b(int** B, int n_b, int m_b) {
    int** B_T = allocate_matrix(m_b, n_b);
    for (int i = 0; i < n_b; i++) {
        for (int j = 0; j < m_b; j++) {
            B_T[j][i] = B[i][j];
        }
    }
    return B_T;
}

// 3. Матричний добуток A x B (повертає нову динамічну матрицю C розміру n_a x m_b)
int** mult_a_b(int** B, int n_b, int m_b, int** A, int n_a) {
    if (n_a != n_b) {
        printf("[!] Помилка: Кількість стовпців A (%d) не дорівнює кількості рядків B (%d)!\n", n_a, n_b);
        return NULL;
    }

    int** C = allocate_matrix(n_a, m_b);
    for (int i = 0; i < n_a; i++) {
        for (int j = 0; j < m_b; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n_a; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

// 4. Сортування елементів матриці A (за зростанням)
void sort_matrix_a(int** A, int n_a, int row_index) {
    if (row_index >= 0 && row_index < n_a) {
        // Сортування лише обраного рядка (метод бульбашки)
        for (int i = 0; i < n_a - 1; i++) {
            for (int j = 0; j < n_a - i - 1; j++) {
                if (A[row_index][j] > A[row_index][j + 1]) {
                    int temp = A[row_index][j];
                    A[row_index][j] = A[row_index][j + 1];
                    A[row_index][j + 1] = temp;
                }
            }
        }
        printf("Рядок %d успішно відсортовано.\n", row_index);
    }
    else if (row_index == -1) {
        // Сортування усіх елементів матриці A
        int total = n_a * n_a;
        int* temp = (int*)malloc(total * sizeof(int));
        if (temp == NULL) return;

        // Копіюємо у лінійний масив
        int k = 0;
        for (int i = 0; i < n_a; i++) {
            for (int j = 0; j < n_a; j++) {
                temp[k++] = A[i][j];
            }
        }

        // Сортуємо лінійний масив
        for (int i = 0; i < total - 1; i++) {
            for (int j = 0; j < total - i - 1; j++) {
                if (temp[j] > temp[j + 1]) {
                    int t = temp[j];
                    temp[j] = temp[j + 1];
                    temp[j + 1] = t;
                }
            }
        }

        // Повертаємо відсортовані значення в матрицю A
        k = 0;
        for (int i = 0; i < n_a; i++) {
            for (int j = 0; j < n_a; j++) {
                A[i][j] = temp[k++];
            }
        }

        free(temp);
        printf("Усю матрицю A успішно відсортовано за зростанням.\n");
    }
    else {
        printf("[!] Некоректний індекс рядка!\n");
    }
}

// 5. Сума елементів рядків A та стовпців B
void print_sums(int** A, int n_a, int** B, int n_b, int m_b) {
    printf("\n--- Суми елементів рядків матриці A ---\n");
    for (int i = 0; i < n_a; i++) {
        int row_sum = 0;
        for (int j = 0; j < n_a; j++) {
            row_sum += A[i][j];
        }
        printf("Рядок %d: %d\n", i, row_sum);
    }

    printf("\n--- Суми елементів стовпців матриці B ---\n");
    for (int j = 0; j < m_b; j++) {
        int col_sum = 0;
        for (int i = 0; i < n_b; i++) {
            col_sum += B[i][j];
        }
        printf("Стовпець %d: %d\n", j, col_sum);
    }
}

