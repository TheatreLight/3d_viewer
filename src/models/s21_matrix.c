#include "s21_matrix.h"

/**
 * Создание матрицы
 */
matrix_t s21_create_matrix(int rows, int columns) {
    matrix_t matrix;
    if (rows > 0 && columns > 0) {
        matrix.rows = rows;
        matrix.columns = columns;
        matrix.matrix = (double **)calloc(rows, sizeof(double*));
        for (int i = 0; i < rows; i++) {
            matrix.matrix[i] = (double *)calloc(columns, sizeof(double));
            for (int j = 0; j < columns; j++) {
                matrix.matrix[i][j] = 0.0;
            }
        }
        matrix.matrix_type = ZERO_MATRIX;
    } else {
        s21_clean_matrix(&matrix);
    }
    return matrix;
}

/**
 * Очистка матрицы
 */
void s21_remove_matrix(matrix_t *A) {
    if (A != NULL) {
        if (A->matrix != NULL) {
            for (int i = 0; i < A->rows; i++) {
                if (A->matrix[i] != NULL) {
                    free(A->matrix[i]);
                }
            }
            free(A->matrix);
        }
    }
    s21_clean_matrix(A);
}

/**
 * Сравнение матрицы
 */
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    int is_eqals = SUCCESS;
    if (A == NULL || B == NULL) {
        return FAILURE;
    }
    if (A->matrix_type == INCORRECT_MATRIX || B->matrix_type == INCORRECT_MATRIX) {
        is_eqals = FAILURE;
    } else if ((A->matrix_type == IDENTITY_MATRIX && B->matrix_type == IDENTITY_MATRIX)
            || (A->matrix_type == ZERO_MATRIX && B->matrix_type == ZERO_MATRIX)) {
        if (A->rows != B->rows && A->columns != B->columns) {
            is_eqals = FAILURE;
        }
    } else if (A->rows != B->rows || A->columns != B->columns) {
        is_eqals = FAILURE;
    } else if ((A->matrix_type == ZERO_MATRIX && B->matrix_type == IDENTITY_MATRIX)
            || (A->matrix_type == IDENTITY_MATRIX && B->matrix_type == ZERO_MATRIX)) {
        is_eqals = FAILURE;
    } else {
        for (int i = 0; i < A->rows; i++) {
            if (A->matrix == NULL || A->matrix[i] == NULL || is_eqals == FAILURE) {
                is_eqals = FAILURE;
                break;
            }
            for (int j = 0; j < A->columns; j ++) {
                double sub = A->matrix[i][j] - B->matrix[i][j];
                sub = sub < 0? - sub: sub;
                if (sub > 1e-6) {
                    is_eqals = FAILURE;
                    break;
                }
            }
        }
    }
    return is_eqals;
}

/**
 * Умножение матрицы
 */
matrix_t s21_mult_matrix(matrix_t *A, matrix_t *B) {
    matrix_t matrix;
    if (A == NULL || B == NULL || A->matrix_type == INCORRECT_MATRIX
            || B->matrix_type == INCORRECT_MATRIX || A->columns != B->rows) {
        s21_clean_matrix(&matrix);
        return matrix;
    }
    matrix = s21_create_matrix(A->rows, B->columns);
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.columns; j ++) {
            double sum = 0.0;
            for (int k = 0; k < A->columns; k ++) {
                sum = sum + A->matrix[i][k] * B->matrix[k][j];
            }
            matrix.matrix[i][j] = matrix.matrix[i][j] + sum;
        }
    }
    matrix.matrix_type = CORRECT_MATRIX;
    s21_fix_type(&matrix);
    return matrix;
}

/**
 * Зануление матрицы после очистки
 */
void s21_clean_matrix(matrix_t *A) {
    if (A != NULL) {
        A->rows = 0;
        A->columns = 0;
        A->matrix_type = INCORRECT_MATRIX;
        A->matrix = NULL;
    }
}

/**
 * Проверка матрицы и исправление ее типа
 */
void s21_fix_type(matrix_t *A) {
    int rows = A->rows;
    int columns = A->columns;
    if (A->matrix_type != INCORRECT_MATRIX) {
        matrix_t zero = s21_get_matrix(ZERO_MATRIX, rows, columns);
        if (s21_eq_matrix(A, &zero) == SUCCESS) {
            A->matrix_type = ZERO_MATRIX;
        } else if (rows == columns) {
            matrix_t ident = s21_get_matrix(IDENTITY_MATRIX, rows, columns);
            if (s21_eq_matrix(A, &ident) == SUCCESS) {
                A->matrix_type = IDENTITY_MATRIX;
            } else {
                A->matrix_type = CORRECT_MATRIX;
            }
            s21_remove_matrix(&ident);
        } else if (rows < 1 || columns < 1) {
            A->matrix_type = INCORRECT_MATRIX;
        } else {
            A->matrix_type = CORRECT_MATRIX;
        }
    s21_remove_matrix(&zero);
    }
}

/**
 * Получение матрицы по типу
 */
matrix_t s21_get_matrix(matrix_type_t type, int rows, int columns) {
    double d = 0.0;
    matrix_t matrix = s21_create_matrix(rows, columns);
    if (type == INCORRECT_MATRIX || type < CORRECT_MATRIX || type > ZERO_MATRIX) {
        matrix.matrix_type = type;
    } else if (type == IDENTITY_MATRIX && rows == columns) {
        d = 1.0;
        matrix.matrix_type = type;
    } else if (type == IDENTITY_MATRIX && rows != columns) {
        matrix.matrix_type = INCORRECT_MATRIX;
    } else if (type == CORRECT_MATRIX) {
        matrix.matrix_type = CORRECT_MATRIX;
    }
    for (int i = 0; matrix.matrix_type == IDENTITY_MATRIX && i < matrix.rows; i++) {
        for (int j = 0; j < matrix.rows; j ++) {
            if (i == j) {
                matrix.matrix[i][j] = d;
            }
        }
    }
    return matrix;
}
