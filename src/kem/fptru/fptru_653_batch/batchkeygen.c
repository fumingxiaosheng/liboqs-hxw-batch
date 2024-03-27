#include <stdio.h>
#include <stdlib.h>
#include "params.h"
#include "poly.h"
#include "pack.h"
#include "inverse.h"
#include "cbd.h"
#include "batchkeygen_extern.h"

#if (FPTRU_N == 653)
#include "poly_mul_n653q/radix_ntt_n653.h"
#elif (FPTRU_N == 761)
#include "poly_mul_n761q/radix_ntt_n761.h"
#elif (FPTRU_N == 1277)
#include "poly_mul_n1277q/radix_ntt_n1277.h"
#endif

#if !defined(N_KEYBATCH)
#define N_KEYBATCH (100)
#endif

void keygen_batchtest()
{
  /* test */
  // int16_t temp[FPTRU_N+1];
  // int8_t *_buffer = malloc( sizeof(int8_t)*FPTRU_N*N_KEYBATCH*2 + sizeof(int16_t)*(FPTRU_N)*N_KEYBATCH );
  // // int8_t *f = (int8_t*)  _buffer;
  // int8_t *g = (int8_t*) (_buffer + sizeof(int8_t)*FPTRU_N*N_KEYBATCH);
  // int16_t *_finv = (int16_t*)   (_buffer + sizeof(int8_t)*2*FPTRU_N*N_KEYBATCH);
  // int8_t * ginv = (int8_t*)_finv;
  // int8_t * gs   = ginv;
  // int8_t * v2    = (int8_t*)temp;
  // for(i=0;i<N_KEYBATCH;i++){
  //   for (int j = 0; j < FPTRU_N; j++){
  //     g[i*FPTRU_N+j] = (int8_t) f[i].coeffs[j];
  //   }
  // }
  // for(i=0;i<FPTRU_N;i++) gs[i] = g[i];
  // for(i=1;i<N_KEYBATCH;i++)
  //     crypto_core_mult3((unsigned char *) &gs[i*FPTRU_N],(const unsigned char *) &gs[(i-1)*FPTRU_N],(const unsigned char *) (g+i*FPTRU_N),0);
  // crypto_core_inv3((unsigned char *)v2, (const unsigned char *)&gs[(N_KEYBATCH-1)*FPTRU_N],0,0); // v = gs[(N_KEYBATCH-1)*p]
  // for(i=N_KEYBATCH-1;i>=2;i--) {
  //   crypto_core_mult3((unsigned char *)&ginv[i*FPTRU_N] , (const unsigned char *)v2 , (const unsigned char *)&gs[(i-1)*FPTRU_N],0); // ginv[i]=v*ginv[i-1]
  //   crypto_core_mult3((unsigned char *)v2 , (const unsigned char *)v2 , (const unsigned char *)(g+i*FPTRU_N),0); // v=v*g[i]
  // }
  // crypto_core_mult3((unsigned char *) &ginv[FPTRU_N] , (const unsigned char *)v2 , (const unsigned char *)g,0);
  // crypto_core_mult3((unsigned char *) &ginv[0] , (const unsigned char *)v2 , (const unsigned char *)(g+FPTRU_N),0);

  int i, j;
  poly f[N_KEYBATCH], finv[N_KEYBATCH];
  poly fs[N_KEYBATCH], v;
  poly u[N_KEYBATCH], uinv[N_KEYBATCH];
  for(i=0;i<N_KEYBATCH;i++){
    for (int j = 0; j < FPTRU_N; j++){
      f[i].coeffs[j] = rand() % 9;
      f[i].coeffs[j] = f[i].coeffs[j] - 4;
      u[i].coeffs[j] = f[i].coeffs[j];
    }
    poly_inverse(&uinv[i],&u[i]);
  }

  /* calculate finv */
  for( j = 0; j < FPTRU_N; j++) fs[0].coeffs[j] = f[0].coeffs[j];
  for (i = 1; i < N_KEYBATCH; i++) poly_mul_q1(&fs[i],&fs[i-1],&f[i]);
  poly_inverse(&v,&fs[N_KEYBATCH-1]);
  for(i=N_KEYBATCH-1;i>=2;i--) {
    // poly_mul_q1(&finv[i],&v,&fs[i-1]);
    // poly_mul_q1(&finv[i],&v,&f[1]);
    // poly_mul_q1(&finv[i],&finv[i],&f[0]);
    poly_mul_q1(&finv[i],&v,&f[i-1]);
    for(j = i-2; j >= 0; j--){
      poly_mul_q1(&finv[i],&finv[i],&f[j]);
    }
    poly_mul_q1(&v,&v,&f[i]);
  }
  poly_mul_q1(&finv[1],&v,&f[0]);
  poly_mul_q1(&finv[0],&v,&f[1]);

  for(i=0;i<N_KEYBATCH;i++){
    for (j = 0; j < FPTRU_N; j++){
      if(finv[i].coeffs[j]!=uinv[i].coeffs[j]){
        // printf("%d:%d,%d\n",j,finv[i].coeffs[j],uinv[i].coeffs[j]);
        printf("%d\n",i);
        break;
      }
    }
  }
  printf("over\n");

  return;
}


// int crypto_kem_keygen_fixedbatch(unsigned char *pk,
//                       unsigned char *sk)
// {
//     if( 1 >= N_KEYBATCH ) {
//         int n = N_KEYBATCH;
//         while( n ) {
//             crypto_kem_keypair(pk,sk);
//             pk += PublicKeys_bytes;
//             sk += KemSk_bytes;
//             n--;
//         }
//         return 0;
//     }
    
//     int i;
//     unsigned char coins[N_KEYBATCH*FPTRU_COIN_BYTES];
//     int16_t temp[FPTRU_N+1];
//     int8_t *_buffer = malloc( sizeof(int8_t)*FPTRU_N*N_KEYBATCH*2 + sizeof(int16_t)*(FPTRU_N)*N_KEYBATCH );
//     int8_t *f = (int8_t*) _buffer;
//     int8_t *g = (int8_t*) (_buffer + sizeof(int8_t)*FPTRU_N*N_KEYBATCH);
//     int16_t *_finv = (int16_t*) (_buffer + sizeof(int8_t)*2*FPTRU_N*N_KEYBATCH);

//     /* generate secret keys */
//     for(i=0;i<N_KEYBATCH;i++){
//         randombytes(coins+i*FPTRU_COIN_BYTES, FPTRU_SEEDBYTES);
//         crypto_hash_shake256(coins+i*FPTRU_COIN_BYTES, FPTRU_COIN_BYTES, coins+i*FPTRU_COIN_BYTES, FPTRU_SEEDBYTES);
        
//         cbd2_int8_t(f + i*FPTRU_COIN_BYTES, coins + i*FPTRU_COIN_BYTES);
//         cbd2_int8_t(g + i*FPTRU_COIN_BYTES, coins + i*FPTRU_COIN_BYTES + FPTRU_COIN_BYTES / 2);
//         for (int j = 0; j < FPTRU_N; ++j)
//             f[j+i*FPTRU_COIN_BYTES] = f[j+i*FPTRU_COIN_BYTES] + f[j+i*FPTRU_COIN_BYTES];
//         f[i*FPTRU_COIN_BYTES] += 1;
        
//     }
    

//   crypto_pke_keygen(pk, sk, coins);

//   for (i = 0; i < FPTRU_PKE_PUBLICKEYBYTES; ++i)
//     sk[i + FPTRU_PKE_SECRETKEYBYTES] = pk[i];

//   randombytes(sk + FPTRU_PKE_SECRETKEYBYTES + FPTRU_PKE_PUBLICKEYBYTES, FPTRU_SEEDBYTES);

//   return 0;
// }



// void crypto_pke_keygen(unsigned char *pk,
//                        unsigned char *sk,
//                        const unsigned char coins[FPTRU_COIN_BYTES*N_KEYBATCH])
// {
//   poly f, finv, g, h;

//   poly_sample(&f, coins);
//   poly_sample(&g, coins + FPTRU_COIN_BYTES / 2);

//   poly_double(&f, &f); //f=2f
//   f.coeffs[0] += 1;

//   poly_inverse(&finv, &f); // 1/f
//   poly_mul_q1(&h, &finv, &g); // h=g*finv=g/f
//   poly_int16_tcsubq(&h);

//   pack_pk(pk, &h);
//   pack_sk(sk, &f);
// }
