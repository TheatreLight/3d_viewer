#include <stdio.h>
#include <stdlib.h>

#include "data.h"
#include "polygons.h"

/**
 * Создание
 */
obj_data_t s21_create_data(int vertexes, int facets) {
    obj_data_t obj;
    obj.count_of_vertexes = vertexes;
    obj.count_of_facets = facets;
    obj.numbers_of_vertexes_in_all_facets = 0;
    obj.matrix_3d = s21_create_matrix(vertexes + 1, 3);
    obj.matrix_3d.matrix_type = CORRECT_MATRIX;
    obj.polygons = (polygon_t *) calloc(facets + 1, sizeof(polygon_t));
    for (int i = 0; i <= facets; i++) {
        obj.polygons[i] = s21_create_polygon(3);
    }
    return obj;
}

/**
 * Очистка
 */
void s21_remove_data(obj_data_t *A) {
    if (A != NULL) {
        s21_remove_matrix(&(A->matrix_3d));
        if (A->polygons != NULL) {
            for (int i = 0; i <= A->count_of_facets; i++) {
                s21_remove_polygon(&(A->polygons[i]));
            }
            polygon_t *polygon = A->polygons;
            free(polygon);
        }
    }
}

double *get_vertex_array_from_data(obj_data_t *data, double *d) {
    size_t i = 0;
    for (int j = 1; j <= data->count_of_facets; j++) {
        for (int k = 1; k <= data->polygons[j].numbers_of_vertexes_in_facets; k++) {
            int index = data->polygons[j].vertexes[k];
            d[i] = data->matrix_3d.matrix[index][0];
            i++;
            d[i] = data->matrix_3d.matrix[index][1];
            i++;
            d[i] = data->matrix_3d.matrix[index][2];
            i++;
        }
    }
    return d;
}
