#ifndef CBD_H
#define CBD_H

#include <stdint.h>
#include "params.h"
#include "poly.h"

void cbd2(poly *r, const uint8_t buf[FPTRU_N / 2]);
void cbd3(poly *r, const uint8_t buf[FPTRU_N * 3 / 4]);
void cbd2_small(int8_t *r, const uint8_t buf[FPTRU_COIN_BYTES / 2]);
#endif
