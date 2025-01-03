#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "kex.h"
#include "kem.h"
#include "symmetric.h"

void kex_uake_initA_AKCN(uint8_t *send, uint8_t *tk, uint8_t *sk, const uint8_t *pkb)
{
  crypto_kem_keypair(send, sk);
  crypto_kem_enc_AKCN(send + OSKR_PUBLICKEYBYTES, tk, pkb);//sendA=(pk,ct_tk(pkb))
}

void kex_uake_sharedB_AKCN(uint8_t *send, uint8_t *k, const uint8_t *recv, const uint8_t *skb)
{
  uint8_t buf[2*OSKR_SSBYTES];
  crypto_kem_enc_AKCN(send, buf, recv);//sendB=(ct_kb(pk))
  crypto_kem_dec_AKCN(buf + OSKR_SSBYTES, recv + OSKR_PUBLICKEYBYTES, skb);//buf=(kb,tk)
  kdf_kex(k, buf, 2*OSKR_SSBYTES);//k=kdf(kb,tk)
}

void kex_uake_sharedA_AKCN(uint8_t *k, const uint8_t *recv, const uint8_t *tk, const uint8_t *sk)
{
  unsigned int i;
  uint8_t buf[2*OSKR_SSBYTES];
  crypto_kem_dec_AKCN(buf, recv, sk);
  for(i=0;i<OSKR_SSBYTES;i++)
    buf[i+OSKR_SSBYTES] = tk[i];//buf=(kb,tk)
  
  kdf_kex(k, buf, 2*OSKR_SSBYTES);//k=kdf(kb,tk)
}

void kex_ake_initA_AKCN(uint8_t *send, uint8_t *tk, uint8_t *sk, const uint8_t *pkb)
{
  crypto_kem_keypair(send, sk);
  crypto_kem_enc_AKCN(send + OSKR_PUBLICKEYBYTES, tk, pkb);//sendA=(pk,ct_tk(pkb))
}

void kex_ake_sharedB_AKCN(uint8_t *send, uint8_t *k, const uint8_t* recv, const uint8_t *skb, const uint8_t *pka)
{
  uint8_t buf[3*OSKR_SSBYTES];
  crypto_kem_enc_AKCN(send, buf, recv);
  crypto_kem_enc_AKCN(send + OSKR_CIPHERTEXTBYTES, buf+OSKR_SSBYTES, pka);//sendB=(ct_kb(pk),ct_ka(pka))
  crypto_kem_dec_AKCN(buf+2*OSKR_SSBYTES, recv + OSKR_PUBLICKEYBYTES, skb);//buf=(kb,ka,tk)
  kdf_kex(k, buf, 3*OSKR_SSBYTES);
}

void kex_ake_sharedA_AKCN(uint8_t *k, const uint8_t *recv, const uint8_t *tk, const uint8_t *sk, const uint8_t *ska)
{
  unsigned int i;
  uint8_t buf[3*OSKR_SSBYTES];
  crypto_kem_dec_AKCN(buf, recv, sk);
  crypto_kem_dec_AKCN(buf + OSKR_SSBYTES, recv + OSKR_CIPHERTEXTBYTES, ska);
  for(i=0;i<OSKR_SSBYTES;i++)//buf=(kb,ka,tk)
    buf[i+2*OSKR_SSBYTES] = tk[i];
  kdf_kex(k, buf, 3*OSKR_SSBYTES);
}
