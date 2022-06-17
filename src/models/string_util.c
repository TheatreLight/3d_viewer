#include "string_util.h"

int put_to_str(char **buf, char *format, ...) {
    va_list args;
    va_start(args, format);
    va_list args2;
    va_copy(args2, args);
    int len = 0;
    len = vsnprintf(NULL, 0, format, args) + 1;
    if (*buf == NULL) {
        init_str(buf, len);
    }
    realloc_str(buf, len);
    char *p = *buf;
    len = vsnprintf(p, len, format, args2);
    va_end(args);
    va_end(args2);
    return len;
}

void init_str(char **pointer, int size) {
    *pointer = (char *)calloc(size, sizeof(char));
}

void realloc_str(char **pointer, int size) {
    int len = strlen(*pointer);
    if (size > 10 && size >= len) {
        size = len + (size - len) + 10;
        *pointer = (char *)realloc(*pointer, size * sizeof(char));
    }
}

void free_str(char **pointer) {
    if (pointer != NULL && *pointer != NULL) {
        free((*pointer));
        *pointer = NULL;
    }
}
