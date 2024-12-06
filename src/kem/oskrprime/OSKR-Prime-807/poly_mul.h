#ifndef POLY_MUL_H
#define POLY_MUL_H

#include "params.h"
#include <stdint.h>

void poly_mul_acc(int16_t res[OSKR_N], const int16_t a[OSKR_N], const int16_t b[OSKR_N]);

#endif