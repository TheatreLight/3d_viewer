#ifndef SRC_MODELS_S21_MATRIX_H_
#define SRC_MODELS_S21_MATRIX_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define S21_NAN 0.0 / 0.0 * (-1.0)

//  типа матрицы
typedef enum {
    CORRECT_MATRIX = 0,
    INCORRECT_MATRIX = 1,
    IDENTITY_MATRIX = 2,
    ZERO_MATRIX = 3
} matrix_type_t;

//  структура матрицы
typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
    matrix_type_t matrix_type;
} matrix_t;

// Создание и очистка
matrix_t s21_create_matrix(int rows, int columns);
void s21_remove_matrix(matrix_t *A);

// Сравнение
enum {FAILURE, SUCCESS};
int s21_eq_matrix(matrix_t *A, matrix_t *B);

// Умножение
matrix_t s21_mult_matrix(matrix_t *A, matrix_t *B);

// Second функции
void s21_clean_matrix(matrix_t *A);
void s21_fix_type(matrix_t *A);
matrix_t s21_get_matrix(matrix_type_t type, int rows, int columns);

#endif  // SRC_MODELS_S21_MATRIX_H_
