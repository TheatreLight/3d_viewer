#include <stdio.h>
#include <stdlib.h>

#include "polygons.h"

/**
 * Создание
 */
polygon_t s21_create_polygon(int size) {
    polygon_t polygon;
    polygon.numbers_of_vertexes_in_facets = size;
    polygon.vertexes = (int *)calloc(size + 1, sizeof(int));
    for (int i = 0; i <= size; i++) {
        polygon.vertexes[i] = 0;
    }
    return polygon;
}

/**
 * Очистка
 */
void s21_remove_polygon(polygon_t *A) {
    if (A != NULL) {
        if (A->vertexes != NULL) {
            free(A->vertexes);
        }
    }
}
