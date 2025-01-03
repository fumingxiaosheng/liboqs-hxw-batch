#ifndef SYMMETRIC_H
#define SYMMETRIC_H

#include <stddef.h>
#include <stdint.h>
#include "params.h"
#include "fips202.h"

typedef keccak_state xof_state;

#define XOF_BLOCKBYTES SHAKE128_RATE

#define oskr_shake128_absorb OSKR_NAMESPACE(oskr_shake128_absorb)//xof
void oskr_shake128_absorb(keccak_state *s, const uint8_t seed[OSKR_SYMBYTES], uint8_t x, uint8_t y);
#define oskr_shake256_prf OSKR_NAMESPACE(oskr_shake256_prf)//prf
void oskr_shake256_prf(uint8_t *out, size_t outlen, const uint8_t key[OSKR_SYMBYTES], uint8_t nonce);

//#define hash_h(OUT, IN, INBYTES) sha3_512(OUT, IN, INBYTES)
#define hash_g(OUT, IN, INBYTES) sha3_512(OUT, IN, INBYTES)
#define xof_absorb(STATE, SEED, X, Y) oskr_shake128_absorb(STATE, SEED, X, Y)
#define xof_squeezeblocks(OUT, OUTBLOCKS, STATE) shake128_squeezeblocks(OUT, OUTBLOCKS, STATE)
#define prf(OUT, OUTBYTES, KEY, NONCE) oskr_shake256_prf(OUT, OUTBYTES, KEY, NONCE)
#define kdf(OUT, IN, INBYTES) sha3_512(OUT, IN, INBYTES) 
#define kdf1(OUT, IN, INBYTES) shake256(OUT, OSKR_SYMBYTES, IN, INBYTES)
#define kdf_kex(OUT, IN, INBYTES) sha3_256(OUT, IN, INBYTES)
#define PREFIXLEN 33

#endif 



