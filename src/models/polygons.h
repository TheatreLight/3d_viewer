#ifndef SRC_MODELS_POLYGONS_H_
#define SRC_MODELS_POLYGONS_H_

#include <stdlib.h>

typedef struct Polygon {
    int *vertexes;
    int numbers_of_vertexes_in_facets;
} polygon_t;

// Создание и очистка
polygon_t s21_create_polygon(int size);
void s21_remove_polygon(polygon_t *A);

#endif  // SRC_MODELS_POLYGONS_H_
