#ifndef NTT_H
#define NTT_H

#include <stdint.h>
#include "params.h"

#define ntt OSKR_NAMESPACE(ntt)
void ntt(int32_t a_star[N_PRIME], int16_t a[OSKR_N]);

#define invntt OSKR_NAMESPACE(invntt)
void invntt(int16_t a[OSKR_N], int32_t a_star[N_PRIME]);

#define poly_pointwise OSKR_NAMESPACE(poly_pointwise)
void poly_pointwise(int32_t c[N_PRIME], 
                    const int32_t a[N_PRIME], 
                    const int32_t b[N_PRIME]);

#endif
