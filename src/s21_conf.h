#ifndef SRC_S21_CONF_H_
#define SRC_S21_CONF_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define _INVALID_CONF 0
#define _VALID_CONF 1

typedef struct Conf_data {
    bool isOrtho, isWire, isNoPoint, isCircle;
    float widthLine, widthPoint, red, green, blue,
    redP, greenP, blueP, redB, greenB, blueB;
    int isValid;
} conf_data_t;

conf_data_t read_config(void);
int save_config(conf_data_t data);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // SRC_S21_CONF_H_
