#ifndef SRC_MODELS_AFFINITY_H_
#define SRC_MODELS_AFFINITY_H_

#include <math.h>
#include <stdio.h>
#include <string.h>

#include "data.h"
#include "s21_matrix.h"
#include "string_util.h"

#define _AFFINITY_ERROR_ {}

void s21_move(obj_data_t *data, double x, double y, double z);
void s21_scale(obj_data_t *data, double scale);
void s21_rotate(obj_data_t *data, double x, double y, double z);

#endif  // SRC_MODELS_AFFINITY_H_
