#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include "params-807.h"
#include "indcpa-807.h"
#include "polyvec-807.h"
#include "poly-807.h"
#include "ntt-807.h"
#include "symmetric-807.h"
#include "randombytes-807.h"

/*************************************************
* Name:        pack_pk
*
* Description: Serialize the public key as concatenation of the
*              serialized vector of polynomials pk
*              and the public seed used to generate the matrix A.
*
* Arguments:   uint8_t *r: pointer to the output serialized public key
*              polyvec *pk: pointer to the input public-key polyvec
*              const uint8_t *seed: pointer to the input public seed
**************************************************/
static void pack_pk(uint8_t r[OSKR_INDCPA_PUBLICKEYBYTES], polyvec *pk, const uint8_t seed[OSKR_SYMBYTES]) {
    size_t i;

    polyvec_tobytes(r, pk);
    for(i=0;i<OSKR_SYMBYTES;i++)
          r[i+OSKR_POLYVECBYTES] = seed[i];
}

/*************************************************
* Name:        unpack_pk
*
* Description: De-serialize public key from a byte array;
*              approximate inverse of pack_pk
*
* Arguments:   - polyvec *pk: pointer to output public-key polynomial vector
*              - uint8_t *seed: pointer to output seed to generate matrix A
*              - const uint8_t *packedpk: pointer to input serialized public key
**************************************************/
static void unpack_pk(polyvec *pk, uint8_t seed[OSKR_SYMBYTES], const uint8_t packedpk[OSKR_INDCPA_PUBLICKEYBYTES]) {
    size_t i;

    polyvec_frombytes(pk, packedpk);// pk
    for(i=0;i<OSKR_SYMBYTES;i++)// ρ
      seed[i] = packedpk[i+OSKR_POLYVECBYTES];
}

/*************************************************
* Name:        pack_sk
*
* Description: Serialize the secret key
*
* Arguments:   - uint8_t *r: pointer to output serialized secret key
*              - polyvec *sk: pointer to input vector of polynomials (secret key)
**************************************************/
static void pack_sk(uint8_t r[OSKR_INDCPA_SECRETKEYBYTES], polyvec *sk) {
    polyvec_eta_tobytes(r, sk);
}

/*************************************************
* Name:        unpack_sk
*
* Description: De-serialize the secret key; inverse of pack_sk
*
* Arguments:   - polyvec *sk: pointer to output vector of polynomials (secret key)
*              - const uint8_t *packedsk: pointer to input serialized secret key
**************************************************/
static void unpack_sk(polyvec *sk, const uint8_t packedsk[OSKR_INDCPA_SECRETKEYBYTES]) {
    polyvec_eta_frombytes(sk, packedsk);
}

/*************************************************
* Name:        pack_ciphertext
*
* Description: Serialize the ciphertext as concatenation of the
*              compressed and serialized vector of polynomials b
*              and the compressed and serialized polynomial v
*
* Arguments:   uint8_t *r: pointer to the output serialized ciphertext
*              poly *pk: pointer to the input vector of polynomials b
*              poly *v: pointer to the input polynomial v
**************************************************/
/*static void pack_ciphertext(uint8_t r[OSKR_INDCPA_CTBYTES], polyvec *u, poly *v){
  polyvec_compress(r, u);
  poly_compress_4(r+OSKR_POLYVECCOMPRESSEDBYTES_CU, v);
}*/


/*************************************************
* Name:        unpack_ciphertext
*
* Description: De-serialize and decompress ciphertext from a byte array;
*              approximate inverse of pack_ciphertext
*
* Arguments:   - polyvec *b: pointer to the output vector of polynomials b
*              - poly *v: pointer to the output polynomial v
*              - const uint8_t *c: pointer to the input serialized ciphertext
**************************************************/
/*static void unpack_ciphertext(polyvec *u, poly *v, const uint8_t c[OSKR_INDCPA_CTBYTES]){
  polyvec_decompress(u, c);
  poly_decompress_4(v, c+OSKR_POLYVECCOMPRESSEDBYTES_CU);
}*/

/*************************************************
* Name:        indcpa_keypair
*
* Description: Generates public and private key for the CPA-secure
*              public-key encryption scheme underlying OSKR
*
* Arguments:   - uint8_t *pk: pointer to output public key
*                             (of length OSKR_INDCPA_PUBLICKEYBYTES bytes)
*              - uint8_t *sk: pointer to output private key
                              (of length OSKR_INDCPA_SECRETKEYBYTES bytes)
**************************************************/
void indcpa_keypair(uint8_t pk[OSKR_INDCPA_PUBLICKEYBYTES],
                    uint8_t sk[OSKR_INDCPA_SECRETKEYBYTES]) {
    uint8_t buf[2 * OSKR_SYMBYTES];// ρ,σ
    const uint8_t *publicseed = buf;
    const uint8_t *noiseseed = buf + OSKR_SYMBYTES;
    uint8_t nonce = 0;
    polyvec a[OSKR_K], e, t, s;
    polyvec_p a_star[OSKR_K], t_star, s_star;

    randombytes(buf, OSKR_SYMBYTES);// d
    hash_g(buf, buf, OSKR_SYMBYTES);// ρ,σ

    gen_a(a, publicseed);// matrix A
    polyvec_getnoise_eta1(&s, noiseseed, nonce++);//s
    polyvec_getnoise_eta1(&e, noiseseed, nonce++);//e

    polyvec_matrix_ntt(a_star, a);
    polyvec_ntt(&s_star, &s);

    polyvec_matrix_basemul(&t_star, a_star, &s_star);
    polyvec_invntt(&t, &t_star);

    polyvec_add(&t, &t, &e);
    polyvec_reduce(&t);

    pack_sk(sk, &s);
    pack_pk(pk, &t, publicseed);
}

/*************************************************
* Name:        indcpa_enc
*
* Description: Encryption function of the CPA-secure
*              public-key encryption scheme underlying OSKR.
*
* Arguments:   - uint8_t *c: pointer to output ciphertext
*                            (of length OSKR_INDCPA_BYTES bytes)
*              - const uint8_t *m: pointer to input message
*                                  (of length OSKR_INDCPA_MSGBYTES bytes)
*              - const uint8_t *pk: pointer to input public key
*                                   (of length OSKR_INDCPA_PUBLICKEYBYTES)
*              - const uint8_t *coins: pointer to input random coins used as seed
*                                      (of length OSKR_SYMBYTES) to deterministically
*                                      generate all randomness
**************************************************/
void indcpa_enc_AKCN(uint8_t c[OSKR_INDCPA_CTBYTES],
                     const uint8_t m[OSKR_INDCPA_MSGBYTES],
                     const uint8_t pk[OSKR_INDCPA_PUBLICKEYBYTES],
                     const uint8_t coins[OSKR_SYMBYTES]) {// coins=r

    uint8_t seed[OSKR_SYMBYTES];
    uint8_t nonce = 0;
    polyvec r, t, e1, at[OSKR_K], u;
    poly v, e2;
    polyvec_p r_star, t_star, at_star[OSKR_K], u_star;
    poly_p v_star;

    unpack_pk(&t, seed, pk);// t rho

    gen_at(at, seed);
    polyvec_getnoise_eta1(&r, coins, nonce++);//r
    polyvec_getnoise_eta2(&e1, coins, nonce++);//e1
    poly_getnoise_eta2(&e2, coins, nonce++);//e2

    polyvec_matrix_ntt(at_star, at);
    polyvec_ntt(&t_star, &t);
    polyvec_ntt(&r_star, &r);

    polyvec_matrix_basemul(&u_star, at_star, &r_star);//AT·r
    polyvec_basemul(&v_star, &t_star, &r_star);// t · r

    polyvec_invntt(&u, &u_star);// 正常域的AT·r
    poly_invntt(&v, &v_star);// 正常域的 t·r

    polyvec_add(&u, &u, &e1);//u = AT·r + e1
    poly_add(&v, &v, &e2);// t·r + e2

    polyvec_reduce(&u);//u
    polyvec_compress(c, &u);//compress_u
    poly_con(c + OSKR_POLYVECCOMPRESSEDBYTES_CU, &v, m);
}
/*
void indcpa_enc_kyber(uint8_t c[OSKR_INDCPA_CTBYTES],
                      const uint8_t m[OSKR_INDCPA_MSGBYTES],
                      const uint8_t pk[OSKR_INDCPA_PUBLICKEYBYTES],
                      const uint8_t coins[OSKR_SYMBYTES]) {// coins=r
    
    uint8_t seed[OSKR_SYMBYTES];
    uint8_t nonce = 0;
    polyvec r, t, e1, at[OSKR_K], u;
    poly v, e2;
    polyvec_p r_star, t_star, at_star[OSKR_K], u_star;
    poly_p v_star;

    poly mp;
    poly_frommsg(&mp, m); // Decompress(msg,dm) 0 or q/2

    unpack_pk(&t, seed, pk);// t rho

    gen_at(at, seed);
    polyvec_getnoise_eta1(&r, coins, nonce++);//r
    polyvec_getnoise_eta2(&e1, coins, nonce++);//e1
    poly_getnoise_eta2(&e2, coins, nonce++);//e2

    polyvec_matrix_ntt(at_star, at);
    polyvec_ntt(&t_star, &t);
    polyvec_ntt(&r_star, &r);

    polyvec_matrix_basemul(&u_star, at_star, &r_star);//AT·r
    polyvec_basemul(&v_star, &t_star, &r_star);// t · r

    polyvec_invntt(&u, &u_star);// 正常域的AT·r
    poly_invntt(&v, &v_star);// 正常域的 t·r

    polyvec_add(&u, &u, &e1);//u = AT·r + e1
    poly_add(&v, &v, &e2);// t·r + e2

    poly_add(&v, &v, &mp);//v = t·r + e2 + Decompress(m)
    polyvec_reduce(&u);//u
    poly_reduce(&v);//v
    pack_ciphertext(c, &u, &v);// c1||c2

}*/

/*************************************************
* Name:        indcpa_dec
*
* Description: Decryption function of the CPA-secure
*              public-key encryption scheme underlying OSKR.
*
* Arguments:   - uint8_t *m: pointer to output decrypted message
*                            (of length OSKR_INDCPA_MSGBYTES)
*              - const uint8_t *c: pointer to input ciphertext
*                                  (of length OSKR_INDCPA_BYTES)
*              - const uint8_t *sk: pointer to input secret key
*                                   (of length OSKR_INDCPA_SECRETKEYBYTES)
**************************************************/
void indcpa_dec_AKCN(uint8_t m[OSKR_INDCPA_MSGBYTES],
                     const uint8_t c[OSKR_INDCPA_CTBYTES],
                     const uint8_t sk[OSKR_INDCPA_SECRETKEYBYTES]) {
    polyvec u, s;
    polyvec_p u_star, s_star;
    poly mp;
    poly_p mp_star;

    polyvec_decompress(&u, c);// u
    unpack_sk(&s, sk);// s

    polyvec_ntt(&s_star, &s);
    polyvec_ntt(&u_star, &u);

    polyvec_basemul(&mp_star, &s_star, &u_star);
    poly_invntt(&mp, &mp_star);// s·u

    poly_rec(m, c + OSKR_POLYVECCOMPRESSEDBYTES_CU, &mp);
}
/*
void indcpa_dec_kyber(uint8_t m[OSKR_INDCPA_MSGBYTES],
                      const uint8_t c[OSKR_INDCPA_CTBYTES],
                      const uint8_t sk[OSKR_INDCPA_SECRETKEYBYTES]) {
    polyvec u, s;
    polyvec_p u_star, s_star;
    poly mp;
    poly_p mp_star;

    poly v;
    unpack_ciphertext(&u, &v, c);// u v

    unpack_sk(&s, sk);// s

    polyvec_ntt(&s_star, &s);
    polyvec_ntt(&u_star, &u);

    polyvec_basemul(&mp_star, &s_star, &u_star);
    poly_invntt(&mp, &mp_star);// s·u

    poly_sub(&mp, &v, &mp);// v-su
    poly_reduce(&mp);
    poly_tomsg(m, &mp);
}*/
