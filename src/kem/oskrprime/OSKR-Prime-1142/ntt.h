#ifndef NTT_H
#define NTT_H

#include <stdint.h>
#include "params.h"

#define ntt OSKR_NAMESPACE(ntt)
void ntt(int32_t a_star[1152], int16_t a[571]);

#define invntt OSKR_NAMESPACE(invntt)
void invntt(int16_t a[571], int32_t a_star[1152]);

#define ntt_naive OSKR_NAMESPACE(ntt_naive)
void ntt_naive(int32_t r[1152]);

#define poly_pointwise OSKR_NAMESPACE(poly_pointwise)
void poly_pointwise(int32_t c[1152], 
                    const int32_t a[1152], 
                    const int32_t b[1152]);

#define invtntt_naive OSKR_NAMESPACE(invtntt_naive)
void invtntt_naive(int32_t r[1152]);

#define poly_reduction OSKR_NAMESPACE(poly_reduction)
void poly_reduction(int16_t r[571], 
                    const int32_t a[1152]);

#define poly_padding OSKR_NAMESPACE(poly_padding)
void poly_padding(int32_t r[1152], 
                  const int16_t a[571]);


#endif
