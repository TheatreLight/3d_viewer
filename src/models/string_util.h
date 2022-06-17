#ifndef SRC_MODELS_STRING_UTIL_H_
#define SRC_MODELS_STRING_UTIL_H_

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int put_to_str(char **buf, char *format, ...);
void init_str(char **pointer, int size);
void realloc_str(char **pointer, int size);
char *check_point(char *string);
void free_str(char **pointer);
void s21_check_zero_end(char **src);

#endif  // SRC_MODELS_STRING_UTIL_H_
