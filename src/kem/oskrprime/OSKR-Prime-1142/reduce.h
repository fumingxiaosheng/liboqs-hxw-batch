#ifndef REDUCE_H
#define REDUCE_H

#include <stdint.h>
#include "params.h"


#define QINV 2018848385 // Q^-1 mod 2^32
#define qINV 12857 // q^-1 mod 2^32


#define montgomery_reduceQ OSKR_NAMESPACE(montgomery_reduceQ)
int32_t montgomery_reduceQ(int64_t a);
#define fQmul OSKR_NAMESPACE(fQmul)
int32_t fQmul(int32_t a, int32_t b);

#define montgomery_reduceq OSKR_NAMESPACE(montgomery_reduceq)
int16_t montgomery_reduceq(int32_t a);
#define fqmul OSKR_NAMESPACE(fqmul)
int16_t fqmul(int16_t a, int16_t b);

#define barrett_reduceq OSKR_NAMESPACE(barrett_reduceq)
int16_t barrett_reduceq(int16_t a);

#define reduce32to16 OSKR_NAMESPACE(reduce32to16)
int16_t reduce32to16(int32_t a);

#define caddq OSKR_NAMESPACE(caddq)
int16_t caddq(int16_t a);

#endif
