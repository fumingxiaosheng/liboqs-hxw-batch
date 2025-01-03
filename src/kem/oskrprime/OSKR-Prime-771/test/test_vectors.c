/* Deterministic randombytes by Daniel J. Bernstein */
/* taken from SUPERCOP (https://bench.cr.yp.to)     */
#include "../fips202.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "../params.h"
#include "../kem.h"
#include "../indcpa.h"
#include "../polyvec.h"
#include "../poly.h"
#include "../randombytes.h"

#define NTESTS 1

/*static uint8_t seed_test[64] = {
  3,1,4,1,5,9,2,6,5,3,5,8,9,7,9,3,2,3,8,4,6,2,6,4,3,3,8,3,2,7,9,5,
  3,1,4,1,5,9,2,6,5,3,5,8,9,7,9,3,2,3,8,4,6,2,6,4,3,3,8,3,2,7,9,5
};
static uint8_t coins[64] = {
  3,1,4,1,5,9,2,6,5,3,5,8,9,7,9,3,2,3,8,4,6,2,6,4,3,3,8,3,2,7,9,5,
  3,1,4,1,5,9,2,6,5,3,5,8,9,7,9,3,2,3,8,4,6,2,6,4,3,3,8,3,2,7,9,5
};*/
/*static uint8_t m[64] = {
  3,255,4,1,5,9,2,6,5,3,5,8,9,7,9,3,2,3,8,4,6,2,6,4,3,3,8,3,2,7,9,5,
  3,1,4,1,5,9,2,6,5,3,5,8,9,7,9,3,2,3,8,4,6,2,6,4,3,3,8,3,2,7,9,5
};*/
/*static uint8_t m[64] = {
  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
};*/
/*static uint8_t m[64] = {
  192,13,97,204,229,170,194,246,86,53,221,28,173,208,179,143,122,228,71,121,198,104,94,93,14,240,180,4,200,150,172,57,175,248,187,201,191,205,47,68,11,102,172,180,210,121,82,155,74,64,133,211,230,15,231,235,72,127,96,143,20,163,222,71
};
static uint8_t coins[64] = {
  124,156,2,92,166,225,217,142,95,252,81,207,157,217,222,57,179,254,109,13,221,204,150,83,233,91,251,77,110,69,227,208,21,117,105,180,41,142,102,202,44,84,85,238,91,101,2,182,205,210,62,88,124,226,176,220,182,175,122,57,154,1,187,6
};*/
/*static uint8_t m[64] = {
  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};*/
/*static uint32_t in[12];
static uint32_t out[8];
static int outleft = 0;

#define ROTATE(x,b) (((x) << (b)) | ((x) >> (32 - (b))))
#define MUSH(i,b) x = t[i] += (((x ^ seed_test[i]) + sum) ^ ROTATE(x,b));

static void surf(void)
{
  uint32_t t[12]; uint32_t x; uint32_t sum = 0;
  int r; int i; int loop;

  for (i = 0;i < 12;++i) t[i] = in[i] ^ seed_test[12 + i];
  for (i = 0;i < 8;++i) out[i] = seed_test[24 + i];
  x = t[11];
  for (loop = 0;loop < 2;++loop) {
    for (r = 0;r < 16;++r) {
      sum += 0x9e3779b9;
      MUSH(0,5) MUSH(1,7) MUSH(2,9) MUSH(3,13)
      MUSH(4,5) MUSH(5,7) MUSH(6,9) MUSH(7,13)
      MUSH(8,5) MUSH(9,7) MUSH(10,9) MUSH(11,13)
    }
    for (i = 0;i < 8;++i) out[i] ^= t[i + 4];
  }
}

void randombytes(uint8_t *x,size_t xlen)
{
  while (xlen > 0) {
    if (!outleft) {
      if (!++in[0]) if (!++in[1]) if (!++in[2]) ++in[3];
      surf();
      outleft = 8;
    }
    *x = out[--outleft];
    printf("%02x", *x);
    ++x;
    --xlen;
  }
  printf("\n");
}*/

void randombytes(uint8_t *out, size_t outlen) {
  unsigned int i;
  uint8_t buf[8];
  static uint64_t ctr = 0;

  for(i = 0; i < 8; ++i)
    buf[i] = ctr >> 8*i;

  ctr++;
  shake128(out, outlen, buf, 8);
}

static void poly_naivemul(poly *c, poly *a, poly *b) {
  unsigned int i,j;
  int16_t t[2*257] = {0};
  for(i = 0; i < 257; ++i)
  {
      for(j = 0; j < 257; ++j)
      {
          t[i+j] = (t[i+j] + (int32_t)a->coeffs[i]*b->coeffs[j]) % q;
      }
  }
  c->coeffs[0] = (t[0] + t[257])%q;
  for(i = 1; i < 256; i++)
    c->coeffs[i] = (t[i + 256] + t[i + 257] + t[i])%q ;
  c->coeffs[256] = (t[256] + t[512])%q;
}

static void poly_matrix_naivemul(polyvec *c, polyvec a[OSKR_K], polyvec *b) {
  unsigned int i,j,k;
  poly t;
  for(i = 0; i < OSKR_K; ++i){
    poly_naivemul(&c->vec[i], &a[i].vec[0], &b->vec[0]);
    for(j = 1; j < OSKR_K; ++j) {
      poly_naivemul(&t, &a[i].vec[j], &b->vec[j]);
      //polyp_add(c->vec[i], c->vec[i], &t);
      for(k = 0; k < OSKR_N; ++k){
        c->vec[i].coeffs[k]=(c->vec[i].coeffs[k] + t.coeffs[k])%Q;
      }
    }
  }
}

static void pack_pk(uint8_t r[OSKR_INDCPA_PUBLICKEYBYTES], polyvec *pk, const uint8_t seed[OSKR_SYMBYTES]) {
    size_t i;

    polyvec_tobytes(r, pk);
    for(i=0;i<OSKR_SYMBYTES;i++)
          r[i+OSKR_POLYVECBYTES] = seed[i];
}

static void unpack_pk(polyvec *pk, uint8_t seed[OSKR_SYMBYTES], const uint8_t packedpk[OSKR_INDCPA_PUBLICKEYBYTES]) {
    size_t i;

    polyvec_frombytes(pk, packedpk);// pk
    for(i=0;i<OSKR_SYMBYTES;i++)// ρ
      seed[i] = packedpk[i+OSKR_POLYVECBYTES];
}

static void pack_sk(uint8_t r[OSKR_INDCPA_SECRETKEYBYTES], polyvec *sk) {
    polyvec_tobytes(r, sk);
}

static void unpack_sk(polyvec *sk, const uint8_t packedsk[OSKR_INDCPA_SECRETKEYBYTES]) {
    unsigned int i,j;
    
    polyvec_frombytes(sk, packedsk);
    for(i = 0; i < OSKR_K; ++i){
      for(j = 0; j < OSKR_N; ++j){
        if(sk->vec[i].coeffs[j] > OSKR_ETA1){
          sk->vec[i].coeffs[j] = sk->vec[i].coeffs[j] - q;
        }
      } 
    }
}

static void pack_ciphertext(uint8_t r[OSKR_INDCPA_CTBYTES], polyvec *u, poly *v)
{
  polyvec_compress(r, u);
  poly_compress_5(r+OSKR_POLYVECCOMPRESSEDBYTES_CU, v);
}

static void unpack_ciphertext(polyvec *u, poly *v, const uint8_t c[OSKR_INDCPA_CTBYTES])
{
  polyvec_decompress(u, c);
  poly_decompress_5(v, c+OSKR_POLYVECCOMPRESSEDBYTES_CU);
}

int main(void)
{
  unsigned int i,j,k,counter;
  unsigned int err_num, eu_num, ev_num;
  uint8_t pk[OSKR_PUBLICKEYBYTES];
  uint8_t sk[OSKR_SECRETKEYBYTES];
  uint8_t ct[OSKR_CIPHERTEXTBYTES];
  uint8_t key_a[OSKR_SSBYTES];
  uint8_t key_b[OSKR_SSBYTES];

  uint8_t nonce = 0;
  uint8_t seed_check[OSKR_SSBYTES];
  uint8_t seed_test[OSKR_SSBYTES];
  uint8_t m[OSKR_SSBYTES];
  uint8_t m_check[OSKR_SSBYTES];
  uint8_t coins[OSKR_SSBYTES];
  polyvec a[OSKR_K], at[OSKR_K], e, e1, r, t, t_check, s, s_check, u, uhat, eu;
  polyvec_p a_star[OSKR_K], at_star[OSKR_K], e_star, e1_star, t_star, s_star, r_star, u_star, eu_star;
  poly v, vhat, e2, mp, mp_check, err1, err2, err3, ev;
  poly_p v_star, mp_star, err1_star, err2_star, err3_star;

  randombytes(m, OSKR_SSBYTES);
  randombytes(seed_test, OSKR_SSBYTES);
  randombytes(coins, OSKR_SSBYTES);

  for(counter=0;counter<NTESTS;counter++) {
    // Key-pair generation
    crypto_kem_keypair(pk, sk);
    /*printf("Public Key: ");
    for(j=0;j<OSKR_PUBLICKEYBYTES;j++)
      printf("%02x",pk[j]);
    printf("\n");
    printf("Secret Key: ");
    for(j=0;j<OSKR_SECRETKEYBYTES;j++)
      printf("%02x",sk[j]);
    printf("\n");*/

    // Encapsulation
    crypto_kem_enc_AKCN(ct, key_b, pk);
    /*printf("Ciphertext: ");
    for(j=0;j<OSKR_CIPHERTEXTBYTES;j++)
      printf("%02x",ct[j]);
    printf("\n");
    printf("Shared Secret B: ");
    for(j=0;j<OSKR_SSBYTES;j++)
      printf("%02x",key_b[j]);
    printf("\n");*/

    // Decapsulation
    crypto_kem_dec_AKCN(key_a, ct, sk);
    /*printf("Shared Secret A: ");
    for(j=0;j<OSKR_SSBYTES;j++)
      printf("%02x",key_a[j]);
    printf("\n");*/

    /*for(j=0;j<OSKR_SSBYTES;j++) {
      if(key_a[j] != key_b[j]) {
        fprintf(stderr, "ERROR\n");
        goto next;
        //return -1;
      }
    }
    next:*/

    /***********keypair***********/

    gen_a(a, seed_test);// matrix A
    /*printf("A = ([");
    for(j = 0; j < OSKR_K; ++j) {
      for(k = 0; k < OSKR_K; ++k) {
        for(i = 0; i < OSKR_N; ++i) {
          printf("%8d", a[j].vec[k].coeffs[i]);
          if(i < OSKR_N-1) printf(", ");
          else if(k < OSKR_K-1) printf("], [");
          else if(j < OSKR_K-1) printf("];\n     [");
          else printf("])\n");
        }
      }
    }*/

    polyvec_getnoise_eta1(&s, seed_test, nonce++);//s
    /*printf("s = ([");
    for(j = 0; j < OSKR_K; ++j) {
      for(k = 0; k < OSKR_N; ++k) {
        printf("%8d", s.vec[j].coeffs[k]);
        if(k < OSKR_N-1) printf(", ");
        else if(j < OSKR_K-1) printf("],\n     [");
        else printf("])\n");
      }
    }*/
    polyvec_getnoise_eta1(&e, seed_test, nonce++);//e

    polyvec_matrix_ntt(a_star, a);
    polyvec_ntt(&s_star, &s);
    polyvec_matrix_basemul(&t_star, a_star, &s_star);
    polyvec_invntt(&t, &t_star);

    //multiplication check
    poly_matrix_naivemul(&t_check, a, &s);
    for(j = 0; j < OSKR_N; ++j) {
      for(k = 0; k < OSKR_K; ++k){
        if((t_check.vec[k].coeffs[j] - t.vec[k].coeffs[j])%q){
          fprintf(stderr, "ERROR in matrix multiplication: t[%d][%d] = %d != %d!\n", k, j, t_check.vec[k].coeffs[j], t.vec[k].coeffs[j]);
          goto next1;
          }
      }
    }

    next1:
    polyvec_add(&t, &t, &e);

    //reduce check
    for(j = 0; j < OSKR_N; ++j) {
      for(k = 0; k < OSKR_K; ++k){
        t_check.vec[k].coeffs[j] = t.vec[k].coeffs[j]%q;
      }
    }
    polyvec_reduce(&t);
    for(j = 0; j < OSKR_N; ++j) {
      for(k = 0; k < OSKR_K; ++k){
        if((t_check.vec[k].coeffs[j] - t.vec[k].coeffs[j])%q){
          fprintf(stderr, "ERROR in reduce!\n");
          goto next2;
          }
      }
    }

    next2:
    pack_sk(sk, &s);
    pack_pk(pk, &t, seed_test);

    //packing check
    unpack_pk(&t_check, seed_check, pk);
    for(i = 0; i < OSKR_K; ++i){
      for(j = 0; j < OSKR_N; ++j){
        if((t.vec[i].coeffs[j] - t_check.vec[i].coeffs[j])%q){
          fprintf(stderr, "ERROR in (un)pack_pk(t)!: t[%d][%d] = %d != %d!\n", i, j, t.vec[i].coeffs[j], t_check.vec[i].coeffs[j]);
          //goto next3;
        }
      }
    }
    //next3:
    for(i = 0; i < OSKR_SYMBYTES; ++i){
      if(seed_test[i] != seed_check[i]){
        fprintf(stderr, "ERROR in (un)pack_pk(seed)!\n");
        goto next4;
      }
    }
    next4:
    unpack_sk(&s_check, sk);
    for(i = 0; i < OSKR_K; ++i){
      for(j = 0; j < OSKR_N; ++j){
        if((s.vec[i].coeffs[j] - s_check.vec[i].coeffs[j])%q){
          fprintf(stderr, "sk: s[%d][%d] = %d != %d!\n", i, j, s.vec[i].coeffs[j], s_check.vec[i].coeffs[j]);
          //fprintf(stderr, "ERROR in (un)pack_sk!\n");
          //goto next5;
        }
      }
    }
    //next5:

    /***********Enc***********/
    gen_at(at, seed_test);
    for(i = 0; i < OSKR_K; ++i){
      for(j = 0; j < OSKR_K; ++j){
        for(k = 0; k < OSKR_N; ++k){
          if(a[i].vec[j].coeffs[k] != at[j].vec[i].coeffs[k]){
            fprintf(stderr, "ERROR in gen_a(t)!\n");
            goto next6;
          }
        }
      }
    }
    next6:
    polyvec_getnoise_eta1(&r, coins, nonce++);//r
    polyvec_getnoise_eta2(&e1, coins, nonce++);//e1
    poly_getnoise_eta2(&e2, coins, nonce++);//e2

    polyvec_matrix_ntt(at_star, at);
    polyvec_ntt(&t_star, &t_check);
    //polyvec_ntt(&t_star, &t);
    polyvec_ntt(&r_star, &r);

    polyvec_matrix_basemul(&u_star, at_star, &r_star);//AT·r
    polyvec_basemul(&v_star, &t_star, &r_star);// t · r

    polyvec_invntt(&u, &u_star);// 正常域的AT·r
    poly_invntt(&v, &v_star);// 正常域的 t·r

    polyvec_add(&u, &u, &e1);//u = AT·r + e1
    poly_add(&v, &v, &e2);// t·r + e2

    //polyvec_reduce(&u);//u
    
    //polyvec_compress(ct, &u);//compress_u
    /*//compress check
    polyvec_decompress(&u_check, ct);
    for(i = 0; i < OSKR_K; ++i){
      for(j = 0; j < OSKR_N; ++j){
        if((u.vec[i].coeffs[j] - u_check.vec[i].coeffs[j])%q){
          fprintf(stderr, "ERROR in polyvec_(de)compress!: t[%d][%d] = %d != %d!\n", i, j, u.vec[i].coeffs[j], u_check.vec[i].coeffs[j]);
          //goto next7;
        }
      }
    }*/
    //next7:
    //poly_con(ct + OSKR_POLYVECCOMPRESSEDBYTES_CU, &v, m);
  
    poly_frommsg(&mp, m);
    poly_frommsg(&mp_check, m);
    //msg check
    poly_tomsg(m_check, &mp);
    for(i = 0; i < OSKR_SYMBYTES; ++i){
      if(m[i] != m_check[i]){
        fprintf(stderr, "ERROR in form/tomsg!: m[%d] = %d != %d!\n", i, m[i], m_check[i]);
        //goto next8;
      }
    }
    poly_add(&v, &v, &mp);//v = t·r + e2 + Decompress(m)
    polyvec_reduce(&u);//u
    poly_reduce(&v);//v
    pack_ciphertext(ct, &u, &v);


    /***********Dec***********/
    //polyvec_decompress(&u, ct);// u

    unpack_ciphertext(&uhat, &vhat, ct);

    polyvec_sub(&eu, &uhat, &u);
    poly_sub(&ev, &vhat, &v);

    polyvec_caddq(&eu);
    for(k = 0; k < OSKR_K; ++k){
      for(j = 0; j < OSKR_N; ++j){
        if(eu.vec[k].coeffs[j]>1961){
          eu.vec[k].coeffs[j] = eu.vec[k].coeffs[j] - q;
        }
      } 
    }
    eu_num = 0;
    for(k = 0; k < OSKR_K; ++k){
      for(j = 0; j < OSKR_N; ++j){
        if(eu.vec[k].coeffs[j]>1){
          fprintf(stderr, "ERROR in eu!: eu[%d][%d] = %d !\n", k, j, eu.vec[k].coeffs[j]);
          fprintf(stderr, "u[%d][%d] = %d !\n", k, j, u.vec[k].coeffs[j]);
          fprintf(stderr, "uhat[%d][%d] = %d !\n", k, j, uhat.vec[k].coeffs[j]);
          eu_num++;
        }
      } 
    }
    printf("eu_num = %d\n",eu_num);

    poly_caddq(&ev);
    for(j = 0; j < OSKR_N; ++j){
      if(ev.coeffs[j]>1961){
        ev.coeffs[j] = ev.coeffs[j] - q;
      }
    }
    ev_num = 0;
    for(j = 0; j < OSKR_N; ++j){
      if(ev.coeffs[j]>31){
        ev_num++;
      }
    }
    printf("ev_num = %d\n",ev_num);
    
    //
    for(k = 0; k < OSKR_K; ++k){
      for(j = 0; j < OSKR_N; ++j){
        if(s_check.vec[k].coeffs[j]>2){
          s_check.vec[k].coeffs[j] = s_check.vec[k].coeffs[j] - q;
        }
      } 
    }
    polyvec_ntt(&s_star, &s_check);

    polyvec_ntt(&u_star, &uhat);
    polyvec_basemul(&mp_star, &s_star, &u_star);
    poly_invntt(&mp, &mp_star);// s·u

    //poly_rec(m_check, ct + OSKR_POLYVECCOMPRESSEDBYTES_CU, &mp);
    poly_sub(&mp, &vhat, &mp);// v-su
    poly_reduce(&mp);

    polyvec_ntt(&e_star, &e);
    polyvec_ntt(&e1_star, &e1);
    polyvec_ntt(&eu_star, &eu);
    polyvec_basemul(&err1_star, &e_star, &r_star);
    polyvec_basemul(&err2_star, &s_star, &e1_star);
    polyvec_basemul(&err3_star, &s_star, &eu_star);
    poly_invntt(&err1, &err1_star);
    poly_invntt(&err2, &err2_star);
    poly_invntt(&err3, &err3_star);

    poly_sub(&err1, &err1, &err2);
    poly_sub(&err1, &err1, &err3);
    poly_add(&err1, &err1, &e2);
    poly_add(&err1, &err1, &ev);
    poly_reduce(&err1);

    poly_caddq(&err1);
    for(j = 0; j < 257; ++j){
      if(err1.coeffs[j]>1961){
        err1.coeffs[j] = err1.coeffs[j] - q;
      }
    }

    //next8:
    err_num = 0;
    for(j = 0; j < 256; ++j){
      if(err1.coeffs[j]>=981){
        err_num++;
      }
    }
    printf("err_num = %d\n",err_num);

    for(j = 0; j < 256; ++j){
      if(((mp_check.coeffs[j] + err1.coeffs[j]) - mp.coeffs[j])%q){
        fprintf(stderr, "ERROR in mp!: mp[%d] = %d != %d + %d\n", j, mp.coeffs[j], mp_check.coeffs[j], err1.coeffs[j]);
        //goto next8;
      }
    }
 
    poly_tomsg(m_check, &mp);
    for(i = 0; i < OSKR_SYMBYTES; ++i){
      if(m[i] != m_check[i]){
        fprintf(stderr, "ERROR in m!: m[%d] = %d != %d!\n", i, m[i], m_check[i]);
        goto next8;
      }
    }
    next8:

    fprintf(stderr, "END\n");


  }

  return 0;
}
