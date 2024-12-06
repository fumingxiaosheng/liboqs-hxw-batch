#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "../kem.h"
#include "../indcpa.h"
#include "../randombytes.h"

#define NTESTS 100000


static int test_pke()
{
  uint8_t pk[OSKR_INDCPA_PUBLICKEYBYTES];
  uint8_t sk[OSKR_INDCPA_SECRETKEYBYTES];
  uint8_t ct[OSKR_INDCPA_CTBYTES];
  uint8_t m[OSKR_INDCPA_MSGBYTES];
  uint8_t m_check[OSKR_INDCPA_MSGBYTES];
  uint8_t coins[OSKR_SYMBYTES];

  
  indcpa_keypair(pk, sk);

  randombytes(m, OSKR_SYMBYTES);
  randombytes(coins, OSKR_SYMBYTES);
  
  indcpa_enc_AKCN(ct, m, pk, coins);
  indcpa_dec_AKCN(m_check, ct, sk);

  if(memcmp(m, m_check, OSKR_SSBYTES)) {
    printf("ERROR m in AKCN\n");
    return 1;
  }
  /*
  indcpa_enc_kyber(ct, m, pk, coins);
  indcpa_dec_kyber(m_check, ct, sk);

  if(memcmp(m, m_check, OSKR_SSBYTES)) {
    printf("ERROR m in kyber\n");
    return 1;
  }
  */
  return 0;
}


static int test_keys()
{
  uint8_t pk[OSKR_PUBLICKEYBYTES];
  uint8_t sk[OSKR_SECRETKEYBYTES_MLKEM];
  uint8_t ct[OSKR_CIPHERTEXTBYTES];
  uint8_t key_a[OSKR_SSBYTES];
  uint8_t key_b[OSKR_SSBYTES];

  //Alice generates a public key
  crypto_kem_keypair_AKCN(pk, sk);

  //Bob derives a secret key and creates a response
  crypto_kem_enc_AKCN(ct, key_b, pk);

  //Alice uses Bobs response to get her shared key
  crypto_kem_dec_AKCN(key_a, ct, sk);

  if(memcmp(key_a, key_b, OSKR_SSBYTES)) {
    printf("ERROR keys in AKCN\n");
    return 1;
  }

  crypto_kem_keypair_mlkem(pk, sk);
  crypto_kem_enc_mlkem(ct, key_b, pk);
  crypto_kem_dec_mlkem(key_a, ct, sk);

  if(memcmp(key_a, key_b, OSKR_SSBYTES)) {
    printf("ERROR keys in mlkem\n");
    return 1;
  }

  crypto_kem_enc_kyber(ct, key_b, pk);
  crypto_kem_dec_kyber(key_a, ct, sk);

  if(memcmp(key_a, key_b, OSKR_SSBYTES)) {
    printf("ERROR keys in kyber\n");
    return 1;
  }

  return 0;
}

static int test_invalid_sk_a()
{
  uint8_t pk[OSKR_PUBLICKEYBYTES];
  uint8_t sk[OSKR_SECRETKEYBYTES];
  uint8_t ct[OSKR_CIPHERTEXTBYTES];
  uint8_t key_a[OSKR_SSBYTES];
  uint8_t key_b[OSKR_SSBYTES];

  //Alice generates a public key
  crypto_kem_keypair_AKCN(pk, sk);

  //Bob derives a secret key and creates a response
  crypto_kem_enc_AKCN(ct, key_b, pk);

  //Replace secret key with random values
  randombytes(sk, OSKR_SECRETKEYBYTES);

  //Alice uses Bobs response to get her shared key
  crypto_kem_dec_AKCN(key_a, ct, sk);

  if(!memcmp(key_a, key_b, OSKR_SSBYTES)) {
    printf("ERROR invalid sk\n");
    return 1;
  }

  return 0;
}

static int test_invalid_ciphertext()
{
  uint8_t pk[OSKR_PUBLICKEYBYTES];
  uint8_t sk[OSKR_SECRETKEYBYTES];
  uint8_t ct[OSKR_CIPHERTEXTBYTES];
  uint8_t key_a[OSKR_SSBYTES];
  uint8_t key_b[OSKR_SSBYTES];
  uint8_t b;
  size_t pos;

  do {
    randombytes(&b, sizeof(uint8_t));
  } while(!b);
  randombytes((uint8_t *)&pos, sizeof(size_t));

  //Alice generates a public key
  crypto_kem_keypair_AKCN(pk, sk);

  //Bob derives a secret key and creates a response
  crypto_kem_enc_AKCN(ct, key_b, pk);

  //Change some byte in the ciphertext (i.e., encapsulated key)
  ct[pos % OSKR_CIPHERTEXTBYTES] ^= b;

  //Alice uses Bobs response to get her shared key
  crypto_kem_dec_AKCN(key_a, ct, sk);

  if(!memcmp(key_a, key_b, OSKR_SSBYTES)) {
    printf("ERROR invalid ciphertext\n");
    return 1;
  }

  return 0;
}

int main(void)
{
  unsigned int i;
  int r;

  for(i=0;i<NTESTS;i++) {
    r  = test_pke();
    r |= test_keys();
    r |= test_invalid_sk_a();
    r |= test_invalid_ciphertext();
    if(r)
      return 1;
  }

  printf("CRYPTO_SECRETKEYBYTES:  %d\n",OSKR_SECRETKEYBYTES);
  printf("CRYPTO_PUBLICKEYBYTES:  %d\n",OSKR_PUBLICKEYBYTES);
  printf("CRYPTO_CIPHERTEXTBYTES: %d\n",OSKR_CIPHERTEXTBYTES);

  return 0;
}
