#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "kem.h"
#include "params.h"
#include "pke.h"
#include "poly.h"
#include "cpucycles.h"
#include "speed.h"
#include "randombytes.h"
#include "pack.h"
#include "symmetric_crypto.h"
#include "batchkeygen_extern.h"

#define NTESTS 100

uint64_t t[NTESTS];


void test_speed_kem()
{
  printf("\n");

  printf("FPTRU-%d-%d-KEM\n\n", FPTRU_N, FPTRU_Q);

  unsigned int i;
  unsigned char pk[FPTRU_KEM_PUBLICKEYBYTES], sk[FPTRU_KEM_SECRETKEYBYTES], ct[FPTRU_KEM_CIPHERTEXTBYTES];
  unsigned char k1[FPTRU_SHAREDKEYBYTES], k2[FPTRU_SHAREDKEYBYTES];

  for (i = 0; i < NTESTS; i++)
  {
    t[i] = cpucycles();
    crypto_kem_keygen(pk, sk);
  }
  print_results("FPTRU_kem_keygen: ", t, NTESTS);

  for (i = 0; i < NTESTS; i++)
  {
    t[i] = cpucycles();
    crypto_kem_encaps(ct, k1, pk);
  }
  print_results("FPTRU_kem_encaps: ", t, NTESTS);

  for (i = 0; i < NTESTS; i++)
  {
    t[i] = cpucycles();
    crypto_kem_decaps(k2, ct, sk);
  }
  print_results("FPTRU_kem_decaps: ", t, NTESTS);


#if !defined(N_KEYBATCH)
#define N_KEYBATCH (10)
#endif
  int j,k;
  poly f[N_KEYBATCH], finv[N_KEYBATCH];
  poly fs[N_KEYBATCH], v;
  poly g[N_KEYBATCH], ginv[N_KEYBATCH];
  for(k=0;k<N_KEYBATCH;k++){
    for (int j = 0; j < FPTRU_N; j++){
      f[k].coeffs[j] = rand() % 9;
      f[k].coeffs[j] = f[k].coeffs[j] - 4;
      g[k].coeffs[j] = f[k].coeffs[j];
    }
  }

  for (i = 0; i < NTESTS; i++)
  {
    t[i] = cpucycles();
    for( j = 0; j < FPTRU_N; j++) fs[0].coeffs[j] = f[0].coeffs[j];
    for (k = 1; k < N_KEYBATCH; k++) poly_mul_q1(&fs[k],&fs[k-1],&f[k]);
    poly_inverse(&v,&fs[N_KEYBATCH-1]);
    for(k=N_KEYBATCH-1;k>=2;k--) {
      poly_mul_q1(&finv[k],&v,&f[k-1]);
      for(j = k-2; j >= 0; j--){
        poly_mul_q1(&finv[k],&finv[k],&f[j]);
      }
      poly_mul_q1(&v,&v,&f[k]);
    }
    poly_mul_q1(&finv[1],&v,&f[0]);
    poly_mul_q1(&finv[0],&v,&f[1]);
  }
  print_results("poly_inverse_batch: ", t, NTESTS);
  
  for (i = 0; i < NTESTS; i++)
  {
    t[i] = cpucycles();
    for(k=0;k<N_KEYBATCH;k++){
      poly_inverse(&ginv[k],&g[k]);
    }
  }
  print_results("poly_inverse: ", t, NTESTS);
}

int main()
{
  test_speed_kem();
  keygen_batchtest();
  return 0;
}
