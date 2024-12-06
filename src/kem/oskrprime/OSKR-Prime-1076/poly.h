#ifndef POLY_H
#define POLY_H

#include <stdint.h>
#include "params.h"

/*
 * Elements of R_q = Z_q[X]/(X^n - x - 1). Represents polynomial
 * coeffs[0] + X*coeffs[1] + X^2*coeffs[2] + ... + X^{n-1}*coeffs[n-1]
 */
typedef struct{
  int16_t coeffs[OSKR_N];
} poly;

typedef struct{
  int32_t coeffs[N_PRIME];
} poly_p;


/* --------- Polynomial Arithmetic --------- */
#define poly_ntt OSKR_NAMESPACE(poly_ntt)
void poly_ntt(poly_p *r, poly *a);
#define poly_invntt OSKR_NAMESPACE(poly_invntt)
void poly_invntt(poly *r, poly_p *a);
#define polyp_pointwisemul OSKR_NAMESPACE(poly_pointwisemul)
void polyp_pointwisemul(poly_p *r, const poly_p *a, const poly_p *b);


#define poly_reduce OSKR_NAMESPACE(poly_reduce)
void poly_reduce(poly *r);
#define poly_caddq OSKR_NAMESPACE(poly_caddq)
void poly_caddq(poly *r);
#define poly_add OSKR_NAMESPACE(poly_add)
void poly_add(poly *r, const poly *a, const poly *b);
#define polyp_add OSKR_NAMESPACE(polyp_add)
void polyp_add(poly_p *r, const poly_p *a, const poly_p *b);
#define poly_sub OSKR_NAMESPACE(poly_sub)
void poly_sub(poly *r, const poly *a, const poly *b);


/* --------- Polynomial Serialization --------- */
/* --------------- compute key ---------------- */
#define poly_frommsg OSKR_NAMESPACE(poly_frommsg)
void poly_frommsg(poly *r, const uint8_t msg[OSKR_INDCPA_MSGBYTES]);
#define poly_tomsg OSKR_NAMESPACE(poly_tomsg)
void poly_tomsg(uint8_t msg[OSKR_INDCPA_MSGBYTES], const poly *a);

#define poly_con OSKR_NAMESPACE(poly_con)
void poly_con(uint8_t r[OSKR_POLYCOMPRESSEDBYTES_CV], poly *v, const uint8_t m[OSKR_INDCPA_MSGBYTES]);
#define poly_rec OSKR_NAMESPACE(poly_rec)
void poly_rec(uint8_t m[OSKR_INDCPA_MSGBYTES], const uint8_t c2[OSKR_POLYCOMPRESSEDBYTES_CV], const poly *su);

/* ------------- generate noise --------------- */
#define poly_getnoise_eta1 OSKR_NAMESPACE(poly_getnoise_eta1)
void poly_getnoise_eta1(poly *r, const uint8_t seed[OSKR_SYMBYTES], uint8_t nonce);
#define poly_getnoise_eta2 OSKR_NAMESPACE(poly_getnoise_eta2)
void poly_getnoise_eta2(poly *r, const uint8_t seed[OSKR_SYMBYTES], uint8_t nonce);

/* ------------ pack uncompressed ------------- */
#define poly_tobytes OSKR_NAMESPACE(poly_tobytes)
void poly_tobytes(uint8_t r[OSKR_POLYBYTES], poly *a);
#define poly_frombytes OSKR_NAMESPACE(poly_frombytes)
void poly_frombytes(poly *r, const uint8_t a[OSKR_POLYBYTES]);

#define polyeta_tobytes OSKR_NAMESPACE(polyeta_tobytes)
void polyeta_tobytes(uint8_t r[OSKR_SECRETBYTES], const poly *a);
#define polyeta_frombytes OSKR_NAMESPACE(polyeta_frombytes)
void polyeta_frombytes(poly *r, const uint8_t a[OSKR_SECRETBYTES]);

/* ------------- pack compressed ------------- */
#define poly_compress_5 OSKR_NAMESPACE(poly_compress_5)
void poly_compress_5(uint8_t r[OSKR_POLYCOMPRESSEDBYTES_CV], poly *a);
#define poly_decompress_5 OSKR_NAMESPACE(poly_decompress_5)
void poly_decompress_5(poly *r, const uint8_t a[OSKR_POLYCOMPRESSEDBYTES_CV]);

#define poly_compress_12 OSKR_NAMESPACE(poly_compress_12)
void poly_compress_12(uint8_t r[OSKR_POLYCOMPRESSEDBYTES_CU], poly *a);
#define poly_decompress_12 OSKR_NAMESPACE(poly_decompress_12)
void poly_decompress_12(poly *r, const uint8_t a[OSKR_POLYCOMPRESSEDBYTES_CU]);

#endif
