#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Func.h"
#include <windows.h>
#include <locale.h>


int main(void) {
    //Локалізація
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, "uk_UA.UTF-8");

    srand((unsigned int)time(NULL));

    int n_a = 21; // За замовчуванням для варіанту 21
    int m_b = 4;  // Довільна кількість стовпців для прямокутної матриці B

    printf("=== Лабораторна робота №4 (Частина 2) | Варіант 21 ===\n");

    // Ввід розмірностей за бажанням користувача
    char change_dim;
    printf("Стандартна розмірність n_a = %d, m_b = %d. Змінити розмірність для тестування? (y/n): ", n_a, m_b);
    scanf(" %c", &change_dim);
    if (change_dim == 'y' || change_dim == 'Y') {
        printf("Введіть розмірність квадратної матриці A (n_a): ");
        scanf("%d", &n_a);
        printf("Введіть кількість стовпців прямокутної матриці B (m_b): ");
        scanf("%d", &m_b);
    }

    int n_b = n_a; // Для виконання множення A * B обов'язково n_b = n_a

    // Виділення динамічної пам'яті під матриці A та B
    int** A = allocate_matrix(n_a, n_a);
    int** B = allocate_matrix(n_b, m_b);

    // Початкове заповнення матриць
    fill_matrix(A, n_a, n_a, "A");
    fill_matrix(B, n_b, m_b, "B");

    // Виведення вхідних матриць
    print_matrix(A, n_a, n_a, "A");
    print_matrix(B, n_b, m_b, "B");

    int choice;
    do {
        printf("\n================ МЕНЮ ================\n");
        printf("1. Вивести поточні матриці A та B\n");
        printf("2. Пошук MAX та MIN вище головної діагоналі (Матриця A)\n");
        printf("3. Транспонувати матрицю B\n");
        printf("4. Обчислити матричний добуток A x B\n");
        printf("5. Сортувати матрицю A (усю або обраний рядок)\n");
        printf("6. Обчислити суми рядків A та стовпців B\n");
        printf("7. Перезаповнити матриці A та B\n");
        printf("0. Вихід з програми\n");
        printf("Ваш вибір: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            print_matrix(A, n_a, n_a, "A");
            print_matrix(B, n_b, m_b, "B");
            break;

        case 2: {
            if (n_a <= 1) {
                printf("\n[!] Матриця занадто мала для знаходження елементів вище головної діагоналі.\n");
            }
            else {
                int max_val, min_val;
                max_min(A, n_a, &max_val, &min_val);
                printf("\n--- Результат завдання 1 (Вище головної діагоналі) ---\n");
                printf("Максимальний елемент: %d\n", max_val);
                printf("Мінімальний елемент: %d\n", min_val);
            }
            break;
        }

        case 3: {
            int** B_T = transpose_b(B, n_b, m_b);
            printf("\n--- Результат завдання 2 (Транспонована матриця B^T) ---\n");
            print_matrix(B_T, m_b, n_b, "B^T");
            free_matrix(B_T, m_b); // Очищення тимчасової матриці
            break;
        }

        case 4: {
            int** C = mult_a_b(B, n_b, m_b, A, n_a);
            if (C != NULL) {
                printf("\n--- Результат завдання 3 (Матричний добуток C = A x B) ---\n");
                print_matrix(C, n_a, m_b, "C");
                free_matrix(C, n_a); // Очищення тимчасової матриці
            }
            break;
        }

        case 5: {
            int sort_opt;
            printf("\n--- Завдання 4: Сортування матриці A ---\n");
            printf("1. Сортувати усю матрицю A за зростанням\n");
            printf("2. Сортувати окремий рядок матриці A\n");
            printf("Ваш вибір: ");
            scanf("%d", &sort_opt);

            if (sort_opt == 1) {
                sort_matrix_a(A, n_a, -1);
                print_matrix(A, n_a, n_a, "A (після сортування)");
            }
            else if (sort_opt == 2) {
                int row;
                printf("Введіть номер рядка (0..%d): ", n_a - 1);
                scanf("%d", &row);
                sort_matrix_a(A, n_a, row);
                print_matrix(A, n_a, n_a, "A (після сортування рядка)");
            }
            else {
                printf("Некоректна опція сортування.\n");
            }
            break;
        }

        case 6:
            print_sums(A, n_a, B, n_b, m_b);
            break;

        case 7:
            fill_matrix(A, n_a, n_a, "A");
            fill_matrix(B, n_b, m_b, "B");
            print_matrix(A, n_a, n_a, "A");
            print_matrix(B, n_b, m_b, "B");
            break;

        case 0:
            printf("\nЗавершення роботи...\n");
            break;

        default:
            printf("\nНекоректний пункт меню. Спробуйте ще раз.\n");
            break;
        }
    } while (choice != 0);

    // Звільнення динамічної пам'яті перед виходом
    free_matrix(A, n_a);
    free_matrix(B, n_b);

    printf("Пам'ять успішно звільнено. Програму завершено.\n");
    return 0;
}