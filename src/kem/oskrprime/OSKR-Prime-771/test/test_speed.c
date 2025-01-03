#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "../kem.h"
#include "../kex.h"
#include "../params.h"
#include "../indcpa.h"
#include "../polyvec.h"
#include "../poly.h"
#include "cpucycles.h"
#include "speed_print.h"

#define NTESTS 100000

uint64_t t[NTESTS];
uint8_t seed[OSKR_SYMBYTES] = {0};

int main()
{
  unsigned int i;
  uint8_t pk[OSKR_PUBLICKEYBYTES];
  uint8_t sk[OSKR_SECRETKEYBYTES];
  uint8_t ct[OSKR_CIPHERTEXTBYTES];
  uint8_t key[OSKR_SSBYTES];
//  polyvec matrix[KYBER_K];
//  poly ap;

  /*for(i=0;i<NTESTS;i++) {
    t[i] = cpucycles();
    gen_matrix(matrix, seed, 0);
  }
  print_results("gen_a: ", t, NTESTS);

  for(i=0;i<NTESTS;i++) {
    t[i] = cpucycles();
    poly_getnoise_etas(&ap, seed, 0);
  }
  print_results("poly_getnoise_etas: ", t, NTESTS);

  for(i=0;i<NTESTS;i++) {
    t[i] = cpucycles();
    poly_getnoise_etae(&ap, seed, 0);
  }
  print_results("poly_getnoise_etae: ", t, NTESTS);

  for(i=0;i<NTESTS;i++) {
    t[i] = cpucycles();
    poly_ntt(&ap);
  }
  print_results("NTT: ", t, NTESTS);

  for(i=0;i<NTESTS;i++) {
    t[i] = cpucycles();
    poly_invntt_tomont(&ap);
  }
  print_results("INVNTT: ", t, NTESTS);

  for(i=0;i<NTESTS;i++) {
    t[i] = cpucycles();
    polyvec_basemul_acc_montgomery(&ap, &matrix[0], &matrix[1]);
  }
  print_results("polyvec_basemul_acc_montgomery: ", t, NTESTS);

  for(i=0;i<NTESTS;i++) {
    t[i] = cpucycles();
    poly_tomsg(ct,&ap);
  }
  print_results("poly_tomsg: ", t, NTESTS);

  for(i=0;i<NTESTS;i++) {
    t[i] = cpucycles();
    poly_frommsg(&ap,ct);
  }
  print_results("poly_frommsg: ", t, NTESTS);

  for(i=0;i<NTESTS;i++) {
    t[i] = cpucycles();
    poly_compress(ct,&ap);
  }
  print_results("poly_compress: ", t, NTESTS);

  for(i=0;i<NTESTS;i++) {
    t[i] = cpucycles();
    poly_decompress(&ap,ct);
  }
  print_results("poly_decompress: ", t, NTESTS);

  for(i=0;i<NTESTS;i++) {
    t[i] = cpucycles();
    polyvec_compress_cu(ct,&matrix[0]);
  }
  print_results("polyvec_compress: ", t, NTESTS);

  for(i=0;i<NTESTS;i++) {
    t[i] = cpucycles();
    polyvec_decompress_cu(&matrix[0],ct);
  }
  print_results("polyvec_decompress: ", t, NTESTS);*/
  
  /*********** ind-cpa pke*************/
  for(i=0;i<NTESTS;i++) {
    t[i] = cpucycles();
    indcpa_keypair(pk, sk);
  }
  print_results("indcpa_keypair: ", t, NTESTS);

  for(i=0;i<NTESTS;i++) {
    t[i] = cpucycles();
    indcpa_enc_AKCN(ct, key, pk, seed);
  }
  print_results("indcpa_enc_AKCN: ", t, NTESTS);

  for(i=0;i<NTESTS;i++) {
    t[i] = cpucycles();
    indcpa_dec_AKCN(key, ct, sk);
  }
  print_results("indcpa_dec_AKCN: ", t, NTESTS);


   /*********** ind-cca kem*************/

  for(i=0;i<NTESTS;i++) {
    t[i] = cpucycles();
    crypto_kem_keypair(pk, sk);
  }
  print_results("keypair: ", t, NTESTS);

  for(i=0;i<NTESTS;i++) {
    t[i] = cpucycles();
    crypto_kem_enc_AKCN(ct, key, pk);
  }
  print_results("AKCN_encaps: ", t, NTESTS);


  for(i=0;i<NTESTS;i++) {
    t[i] = cpucycles();
    crypto_kem_dec_AKCN(key, ct, sk);
  }
  print_results("AKCN_decaps: ", t, NTESTS);

  return 0;
}
