#include <stdint.h>
#include "params.h"
#include "poly.h"
#include "polyvec.h"


/**************************************************************/
/************ Matrix of polynomials **************/
/**************************************************************/

/*************************************************
* Name:        rej_uniform
*
* Description: Run rejection sampling on uniform random bytes to generate
*              uniform random integers mod q
*
* Arguments:   - int16_t *r: pointer to output buffer
*              - unsigned int len: requested number of 16-bit integers (uniform mod q)
*              - const uint8_t *buf: pointer to input buffer (assumed to be uniformly random bytes)
*              - unsigned int buflen: length of input buffer in bytes
*
* Returns number of sampled 16-bit integers (at most len)
**************************************************/
static unsigned int rej_uniform(int16_t *r, unsigned int len, const uint8_t *buf, unsigned int buflen) { // len为生成系数数量
    unsigned int ctr, pos;
    uint16_t val;

    ctr = pos = 0;
    while (ctr < len && pos + 2 <= buflen) {
        val = (buf[pos] | ((uint16_t) buf[pos + 1] << 8)) & 0x1fff;
        pos += 2;

        if (val < q) {
            r[ctr++] = val;
        }
    }
    return ctr;
}

/*************************************************
* Name:        gen_matrix
*
* Description: Deterministically generate matrix A (or the transpose of A)
*              from a seed. Entries of the matrix are polynomials that look
*              uniformly random. Performs rejection sampling on output of
*              a XOF
*
* Arguments:   - polyvec *a: pointer to ouptput matrix A
*              - const uint8_t *seed: pointer to input seed
*              - int transposed: boolean deciding whether A or A^T is generated
**************************************************/
void gen_matrix(polyvec a[OSKR_K], const uint8_t seed[OSKR_SYMBYTES], int transposed) // Not static for benchmarking
{
  unsigned int ctr, i, j;
  unsigned int buflen;
  unsigned char buf[GEN_MATRIX_NBLOCKS*XOF_BLOCKBYTES + 1];
  xof_state state;


  for(i=0;i<OSKR_K;i++) {
    for(j=0;j<OSKR_K;j++) {
      if(transposed)
        xof_absorb(&state, seed, i, j);// i/j作为最后两个byte拼接上seed作为absorb的输入
      else
        xof_absorb(&state, seed, j, i);

      xof_squeezeblocks(buf, GEN_MATRIX_NBLOCKS, &state);// squeeze若干block
      buflen = GEN_MATRIX_NBLOCKS*XOF_BLOCKBYTES;
      ctr = rej_uniform(a[i].vec[j].coeffs, OSKR_N, buf, buflen);

      while (ctr < OSKR_N) {
        xof_squeezeblocks(buf, 1, &state);
        ctr += rej_uniform(a[i].vec[j].coeffs + ctr, OSKR_N - ctr, buf, XOF_BLOCKBYTES);
      }
    }
  }
}


/*************************************************
* Name:        polyvec_matrix_ntt
*
* Description: Forward NTT of all polynomials in matrix of size K*L. 
*
* Arguments:   - polyvecl mat[K]: pointer to input/output matrix
**************************************************/
void polyvec_matrix_ntt(polyvec_p mathat[OSKR_K], polyvec mat[OSKR_K]) {
  unsigned int i, j;

  for(i = 0; i < OSKR_K; i++)
    for(j = 0; j < OSKR_K; j++)
      poly_ntt(&mathat[i].vec[j], &mat[i].vec[j]);
}

/*************************************************
* Name:        polyvec_matrix_basemul
*
* Description: multiplication between matrix(K*K) and vectors(K) in NTT domain. 
**************************************************/
void polyvec_matrix_basemul(polyvec_p *t, const polyvec_p mat[OSKR_K], const polyvec_p *s) {
  unsigned int i;

  for(i = 0; i < OSKR_K; i++)
    polyvec_basemul(&t->vec[i], &mat[i], s);
}

/**************************************************************/
/************ Vectors of polynomials of OSKR_K **************/
/**************************************************************/

/*************************************************
* Name:        polyvec_getnoise_eta1
**************************************************/
void polyvec_getnoise_eta1(polyvec *r, const uint8_t seed[OSKR_SYMBYTES], uint8_t nonce) {
  unsigned int i;

  for (i = 0; i < OSKR_K; i++)
        poly_getnoise_eta1(&r->vec[i], seed, nonce++);// s
}

/*************************************************
* Name:        polyvec_getnoise_eta2
**************************************************/
void polyvec_getnoise_eta2(polyvec *r, const uint8_t seed[OSKR_SYMBYTES], uint8_t nonce) {
  unsigned int i;

  for (i = 0; i < OSKR_K; i++)
        poly_getnoise_eta2(&r->vec[i], seed, nonce++);// s
}

/*************************************************
* Name:        polyvec_compress
*
* Description: Compress and serialize vector of polynomials
*
* Arguments:   - uint8_t *r: pointer to output byte array
*                            (needs space for OSKR_POLYVECCOMPRESSEDBYTES_CU)
*              - const polyvec *a: pointer to input vector of polynomials
**************************************************/
void polyvec_compress(uint8_t r[OSKR_POLYVECCOMPRESSEDBYTES_CU], polyvec *a) {
    unsigned int i;
    for (i = 0; i < OSKR_K; i++)
        poly_compress_11(r + i * OSKR_POLYCOMPRESSEDBYTES_CU, &a->vec[i]);
}

/*************************************************
* Name:        polyvec_decompress
*
* Description: De-serialize and decompress vector of polynomials;
*              approximate inverse of polyvec_compress
*
* Arguments:   - polyvec *r:       pointer to output vector of polynomials
*              - const uint8_t *a: pointer to input byte array
*                                  (of length OSKR_POLYVECCOMPRESSEDBYTES_CU)
**************************************************/
void polyvec_decompress(polyvec *r, const uint8_t a[OSKR_POLYVECCOMPRESSEDBYTES_CU]) {
    unsigned int i;
    for (i = 0; i < OSKR_K; i++)
        poly_decompress_11(&r->vec[i], a + i * OSKR_POLYCOMPRESSEDBYTES_CU);
}

/*************************************************
* Name:        polyvec_tobytes
*
* Description: Serialize vector of polynomials
*
* Arguments:   - uint8_t *r: pointer to output byte array
*                            (needs space for OSKR_POLYVECBYTES)
*              - const polyvec *a: pointer to input vector of polynomials
**************************************************/
void polyvec_tobytes(uint8_t r[OSKR_POLYVECBYTES], polyvec *a) {
    unsigned int i;
    for (i = 0; i < OSKR_K; i++)
        poly_tobytes(r + i * OSKR_POLYBYTES, &a->vec[i]);

}

/*************************************************
* Name:        polyvec_frombytes
*
* Description: De-serialize vector of polynomials;
*              inverse of polyvec_tobytes
*
* Arguments:   - uint8_t *r:       pointer to output byte array
*              - const polyvec *a: pointer to input vector of polynomials
*                                  (of length OSKR_POLYVECBYTES)
**************************************************/
void polyvec_frombytes(polyvec *r, const uint8_t a[OSKR_POLYVECBYTES]) {
    unsigned int i;
    for (i = 0; i < OSKR_K; i++)
        poly_frombytes(&r->vec[i], a + i * OSKR_POLYBYTES);

}

/*************************************************
* Name:        polyvec_eta_tobytes
*
* Description: Serialize vector of polynomials
*
* Arguments:   - uint8_t *r: pointer to output byte array
*                            (needs space for OSKR_POLYVECBYTES)
*              - const polyvec *a: pointer to input vector of polynomials
**************************************************/
void polyvec_eta_tobytes(uint8_t r[OSKR_SECRETVECBYTES], const polyvec *a) {
    unsigned int i;
    for (i = 0; i < OSKR_K; i++)
        polyeta_tobytes(r + i * OSKR_SECRETBYTES, &a->vec[i]);

}

/*************************************************
* Name:        polyvec_eta_frombytes
*
* Description: De-serialize vector of polynomials;
*              inverse of polyvec_tobytes
*
* Arguments:   - uint8_t *r:       pointer to output byte array
*              - const polyvec *a: pointer to input vector of polynomials
*                                  (of length OSKR_POLYVECBYTES)
**************************************************/
void polyvec_eta_frombytes(polyvec *r, const uint8_t a[OSKR_SECRETVECBYTES]) {
    unsigned int i;
    for (i = 0; i < OSKR_K; i++)
        polyeta_frombytes(&r->vec[i], a + i * OSKR_SECRETBYTES);

}

/*************************************************
* Name:        polyvec_ntt
*
* Description: Apply forward NTT to all elements of a vector of polynomials
*
* Arguments:   - polyvec *r: pointer to in/output vector of polynomials
**************************************************/
void polyvec_ntt(polyvec_p *r, polyvec *a) {
    unsigned int i;
    for (i = 0; i < OSKR_K; i++)
        poly_ntt(&r->vec[i], &a->vec[i]);
}

/*************************************************
* Name:        polyvec_invntt_tomont
*
* Description: Apply inverse NTT to all elements of a vector of polynomials
*              and multiply by Montgomery factor 2^16
*
* Arguments:   - polyvec *r: pointer to in/output vector of polynomials
**************************************************/
void polyvec_invntt(polyvec *r, polyvec_p *a) {
    unsigned int i;
    for (i = 0; i < OSKR_K; i++)
        poly_invntt(&r->vec[i], &a->vec[i]);
}

/*************************************************
* Name:        polyvec_basemul
*
* Description: Multiply elements of vectors(K) a and vectors(K) b in NTT domain, accumulate into r,
*              and multiply by 2^-16.
*
* Arguments: - poly *r: pointer to output polynomial
*            - const polyvec *a: pointer to first input vector of polynomials
*            - const polyvec *b: pointer to second input vector of polynomials
**************************************************/
void polyvec_basemul(poly_p *r, const polyvec_p *a, const polyvec_p *b) {
    unsigned int i;
    poly_p t;

    polyp_pointwisemul(r, &a->vec[0], &b->vec[0]);
    for(i=1;i<OSKR_K;i++) {
      polyp_pointwisemul(&t, &a->vec[i], &b->vec[i]);
      polyp_add(r, r, &t);
    }
}

/*************************************************
* Name:        polyvec_reduce
*
* Description: Applies Barrett reduction to each coefficient
*              of each element of a vector of polynomials;
*              for details of the Barrett reduction see comments in reduce.c
*
* Arguments:   - polyvec *r: pointer to input/output polynomial
**************************************************/
void polyvec_reduce(polyvec *r) {
    unsigned int i;
    for (i = 0; i < OSKR_K; i++)
        poly_reduce(&r->vec[i]);
}

/*************************************************
* Name:        polyvec_add
*
* Description: Add vectors of polynomials
*
* Arguments: - polyvec *r: pointer to output vector of polynomials
*            - const polyvec *a: pointer to first input vector of polynomials
*            - const polyvec *b: pointer to second input vector of polynomials
**************************************************/
void polyvec_add(polyvec *r, const polyvec *a, const polyvec *b) {
    unsigned int i;
    for (i = 0; i < OSKR_K; i++)
        poly_add(&r->vec[i], &a->vec[i], &b->vec[i]);
}

void polyvec_sub(polyvec *r, const polyvec *a, const polyvec *b) {
    unsigned int i;
    for (i = 0; i < OSKR_K; i++)
        poly_sub(&r->vec[i], &a->vec[i], &b->vec[i]);
}
/*************************************************
* Name:        polyvec_caddq
*
* Description: For all coefficients of polynomials in vector 
*              add q if coefficient is negative.
*
* Arguments:   - polyvec *r: pointer to input/output vector
**************************************************/
void polyvec_caddq(polyvec *r) {
  unsigned int i;
  for(i = 0; i < OSKR_K; i++)
    poly_caddq(&r->vec[i]);
}
