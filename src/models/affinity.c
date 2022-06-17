#include "affinity.h"

// void print(matrix_t *data) {
//     for(int i = 0; i < data->rows; i++) {
//         for (int j = 0; j < data->columns; j++) {
//             printf("%lf ", data->matrix[i][j]);
//         }
//         printf("%c", '\n');
//     }
// }

/**
 * @brief Функция движения матрицы по осям координат 3д объекта
 * 
 * @param data объект
 */
void s21_move(obj_data_t *data, double x, double y, double z) {
    for (int i = 1; i <= data->count_of_vertexes; i++) {
        matrix_t identity_matrix = s21_get_matrix(IDENTITY_MATRIX, 4, 4);
        for (int j = 0; j < 3; j++) {
            identity_matrix.matrix[j][3] = data->matrix_3d.matrix[i][j];
        }
        s21_fix_type(&identity_matrix);
        matrix_t shift_matrix = s21_create_matrix(4, 1);
        shift_matrix.matrix[0][0] = x;
        shift_matrix.matrix[1][0] = y;
        shift_matrix.matrix[2][0] = z;
        shift_matrix.matrix[3][0] = 1.0;
        s21_fix_type(&shift_matrix);
        matrix_t result_matrix = s21_mult_matrix(&identity_matrix, &shift_matrix);
        for (int j = 0; j < 3; j++) {
            data->matrix_3d.matrix[i][j] = result_matrix.matrix[j][0];
        }
        s21_remove_matrix(&identity_matrix);
        s21_remove_matrix(&shift_matrix);
        s21_remove_matrix(&result_matrix);
    }
}

/**
 * @brief Функиця маштабирования объекта
 * 
 * @param data объект
 * @param scale коэффициент маштабирования
 */
void s21_scale(obj_data_t *data, double scale) {
    for (int i = 1; i <= data->count_of_vertexes; i++) {
        matrix_t identity_matrix = s21_get_matrix(IDENTITY_MATRIX, 3, 3);
        for (int j = 0; j < 3; j++) {
            identity_matrix.matrix[j][j] = scale;
        }
        s21_fix_type(&identity_matrix);
        matrix_t vertex_matrix = s21_create_matrix(3, 1);
        vertex_matrix.matrix[0][0] = data->matrix_3d.matrix[i][0];
        vertex_matrix.matrix[1][0] = data->matrix_3d.matrix[i][1];
        vertex_matrix.matrix[2][0] = data->matrix_3d.matrix[i][2];
        s21_fix_type(&vertex_matrix);
        matrix_t result_matrix = s21_mult_matrix(&identity_matrix, &vertex_matrix);
        for (int j = 0; j < 3; j++) {
            data->matrix_3d.matrix[i][j] = result_matrix.matrix[j][0];
        }
        s21_remove_matrix(&identity_matrix);
        s21_remove_matrix(&vertex_matrix);
        s21_remove_matrix(&result_matrix);
    }
}

double degre_to_radian(double degre) {
    return (degre * M_PI) / 180.0;
}

void s21_rotate(obj_data_t *data, double x, double y, double z) {
    double x_radian = degre_to_radian(x);
    double y_radian = degre_to_radian(y);
    double z_radian = degre_to_radian(z);
    for (int i = 1; i <= data->count_of_vertexes; i++) {
        matrix_t x_matrix = s21_get_matrix(IDENTITY_MATRIX, 3, 3);
        if (x > 1e-6 || x < -1e-6) {
            x_matrix.matrix[1][1] = cos(x_radian);
            x_matrix.matrix[1][2] = -1 * sin(x_radian);
            x_matrix.matrix[2][1] = sin(x_radian);
            x_matrix.matrix[2][2] = cos(x_radian);
            s21_fix_type(&x_matrix);
        }
        matrix_t y_matrix = s21_get_matrix(IDENTITY_MATRIX, 3, 3);
        if (y > 1e-6 || y < -1e-6) {
            y_matrix.matrix[0][0] = cos(y_radian);
            y_matrix.matrix[0][2] = -1 * sin(y_radian);
            y_matrix.matrix[2][0] = sin(y_radian);
            y_matrix.matrix[2][2] = cos(y_radian);
            s21_fix_type(&y_matrix);
        }
        matrix_t z_matrix = s21_get_matrix(IDENTITY_MATRIX, 3, 3);
        if (z > 1e-6 || z < -1e-6) {
            z_matrix.matrix[0][0] = cos(z_radian);
            z_matrix.matrix[0][1] = -1 * sin(z_radian);
            z_matrix.matrix[1][0] = sin(z_radian);
            z_matrix.matrix[1][1] = cos(z_radian);
            s21_fix_type(&z_matrix);
        }
        matrix_t vertex_matrix = s21_create_matrix(3, 1);
        vertex_matrix.matrix[0][0] = data->matrix_3d.matrix[i][0];
        vertex_matrix.matrix[1][0] = data->matrix_3d.matrix[i][1];
        vertex_matrix.matrix[2][0] = data->matrix_3d.matrix[i][2];
        s21_fix_type(&vertex_matrix);
        matrix_t result_x_matrix = s21_mult_matrix(&x_matrix, &vertex_matrix);
        matrix_t result_y_matrix = s21_mult_matrix(&y_matrix, &result_x_matrix);
        matrix_t result_z_matrix = s21_mult_matrix(&z_matrix, &result_y_matrix);
        for (int j = 0; j < 3; j++) {
            data->matrix_3d.matrix[i][j] = result_z_matrix.matrix[j][0];
        }
        s21_remove_matrix(&x_matrix);
        s21_remove_matrix(&y_matrix);
        s21_remove_matrix(&z_matrix);
        s21_remove_matrix(&vertex_matrix);
        s21_remove_matrix(&result_x_matrix);
        s21_remove_matrix(&result_y_matrix);
        s21_remove_matrix(&result_z_matrix);
    }
}
