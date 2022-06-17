#ifndef SRC_MODELS_OBJPARSER_H_
#define SRC_MODELS_OBJPARSER_H_

#include <stdio.h>
#include <string.h>

#include "data.h"
#include "s21_matrix.h"
#include "string_util.h"

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#define _OBJPARSER_ERROR_ { \
"Success", \
"No such file or directory", \
"FEOF error", \
"Incorrect obj file", \
"Vertex parsing error", \
"Facets parsing error" \
}

int objparser(obj_data_t *src, char *file_name);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  // SRC_MODELS_OBJPARSER_H_
