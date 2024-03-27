#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "params.h"
#include "batchkeygen_extern.h"

static int8_t F3_freeze(int16_t x)
{
    return x-3*((10923*x+16384)>>15);
}


int crypto_core_mult3sntrup761_ref(unsigned char *outbytes,const unsigned char *inbytes,const unsigned char *kbytes,const unsigned char *cbytes)
{
    int8_t *h = (void *) outbytes;
    int8_t f[FPTRU_N];
    int8_t g[FPTRU_N];
    int8_t fg[FPTRU_N+FPTRU_N-1];
    int16_t result;
    int i,j;

    for (i = 0;i < FPTRU_N;++i) {
        int8_t fi = inbytes[i];
        int8_t fi0 = fi&1;
        f[i] = fi0-(fi&(fi0<<1));
    }
    for (i = 0;i < FPTRU_N;++i) {
        int8_t gi = kbytes[i];
        int8_t gi0 = gi&1;
        g[i] = gi0-(gi&(gi0<<1));
    }

    for (i = 0;i < FPTRU_N;++i) {
        result = 0;
        for (j = 0;j <= i;++j) result += f[j]*g[i-j];
        fg[i] = F3_freeze(result);
    }
    for (i = FPTRU_N;i < FPTRU_N+FPTRU_N-1;++i) {
        result = 0;
        for (j = i-FPTRU_N+1;j < FPTRU_N;++j) result += f[j]*g[i-j];
        fg[i] = F3_freeze(result);
    }

    for (i = FPTRU_N+FPTRU_N-2;i >= FPTRU_N;--i) {
        fg[i-FPTRU_N] = F3_freeze(fg[i-FPTRU_N]+fg[i]);
        fg[i-FPTRU_N+1] = F3_freeze(fg[i-FPTRU_N+1]+fg[i]);
    }

    for (i = 0;i < FPTRU_N;++i) h[i] = fg[i];
    return 0;
}

static int int16_nonzero_mask(int16_t x)
{
    uint16_t u = x; /* 0, else 1...65535 */
    uint32_t v = u; /* 0, else 1...65535 */
    v = -v; /* 0, else 2^32-65535...2^32-1 */
    v >>= 31; /* 0, else 1 */
    return -v; /* 0, else -1 */
}


static int int16_negative_mask(int16_t x)
{
    uint16_t u = x;
    u >>= 15;
    return -(int) u;
    /* alternative with gcc -fwrapv: */
    /* x>>15 compiles to CPU's arithmetic right shift */
}

int crypto_core_inv3sntrup761_ref(unsigned char *outbytes,const unsigned char *inbytes,const unsigned char *kbytes,const unsigned char *cbytes)
{
    int8_t *out = (void *) outbytes;
    int8_t *in = (void *) inbytes;
    int8_t f[FPTRU_N+1],g[FPTRU_N+1],v[FPTRU_N+1],r[FPTRU_N+1];
    int i,loop,delta;
    int sign,swap,t;

    for (i = 0;i < FPTRU_N+1;++i) v[i] = 0;
    for (i = 0;i < FPTRU_N+1;++i) r[i] = 0;
    r[0] = 1;
    for (i = 0;i < FPTRU_N;++i) f[i] = 0;
    f[0] = 1; f[FPTRU_N-1] = f[FPTRU_N] = -1;
    for (i = 0;i < FPTRU_N;++i) {
        int8_t i1 = in[i]&1;
        g[FPTRU_N-1-i] = i1-(in[i]&(i1<<1));
    }
    g[FPTRU_N] = 0;

    delta = 1;

    for (loop = 0;loop < 2*FPTRU_N-1;++loop) {
        for (i = FPTRU_N;i > 0;--i) v[i] = v[i-1];
        v[0] = 0;

        sign = -g[0]*f[0];
        swap = int16_negative_mask(-delta) & int16_nonzero_mask(g[0]);
        delta ^= swap&(delta^-delta);
        delta += 1;

        for (i = 0;i < FPTRU_N+1;++i) {
            t = swap&(f[i]^g[i]); f[i] ^= t; g[i] ^= t;
            t = swap&(v[i]^r[i]); v[i] ^= t; r[i] ^= t;
        }

        for (i = 0;i < FPTRU_N+1;++i) g[i] = F3_freeze(g[i]+sign*f[i]);
        for (i = 0;i < FPTRU_N+1;++i) r[i] = F3_freeze(r[i]+sign*v[i]);

        for (i = 0;i < FPTRU_N;++i) g[i] = g[i+1];
        g[FPTRU_N] = 0;
    }

    sign = f[0];
    for (i = 0;i < FPTRU_N;++i) out[i] = sign*v[FPTRU_N-1-i];

    out[FPTRU_N] = int16_nonzero_mask(delta);
    return 0;
}