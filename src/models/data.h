#ifndef SRC_MODELS_DATA_H_
#define SRC_MODELS_DATA_H_

#include "polygons.h"
#include "s21_matrix.h"

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

/**
 * @brief Струкрура 3д обекта
 * 
 */
typedef struct Obj_data {
    int count_of_vertexes;
    int count_of_facets;
    int numbers_of_vertexes_in_all_facets;
    matrix_t matrix_3d;
    polygon_t *polygons;
} obj_data_t;

// Создание и очистка
obj_data_t s21_create_data(int vertexes, int facets);
void s21_remove_data(obj_data_t *A);
double *get_vertex_array_from_data(obj_data_t *data, double *d);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  // SRC_MODELS_DATA_H_
