#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "params-807.h"
#include "kem-807.h"
#include "indcpa-807.h"
#include "verify-807.h"
#include "symmetric-807.h"
#include "randombytes-807.h"

/*************************************************
* Name:        crypto_kem_keypair
*
* Description: Generates public and private key
*              for CCA-secure OSKR key encapsulation mechanism
*
* Arguments:   - uint8_t *pk: pointer to output public key
*                (an already allocated array of OSKR_PUBLICKEYBYTES bytes)
*              - uint8_t *sk: pointer to output private key
*                (an already allocated array of OSKR_SECRETKEYBYTES bytes)
*
* Returns 0 (success)
**************************************************/
int crypto_kem_keypair_AKCN(unsigned char *pk, unsigned char *sk)
{
    indcpa_keypair(pk, sk);//CPAPKE's pk sk
    memcpy(sk + OSKR_INDCPA_SECRETKEYBYTES, pk, OSKR_INDCPA_PUBLICKEYBYTES);//(sk||pk)
    randombytes(sk + OSKR_INDCPA_SECRETKEYBYTES + OSKR_INDCPA_PUBLICKEYBYTES, OSKR_SYMBYTES);//pos change (sk||pk||s):=sk
    return 0;
}

int crypto_kem_keypair_mlkem(unsigned char *pk, unsigned char *sk)
{
    indcpa_keypair(pk, sk);//CPAPKE's pk sk
    memcpy(sk + OSKR_INDCPA_SECRETKEYBYTES, pk, OSKR_INDCPA_PUBLICKEYBYTES);//(sk||pk)
    hash_h(sk+OSKR_SECRETKEYBYTES_MLKEM-2*OSKR_SYMBYTES, pk, OSKR_PUBLICKEYBYTES);
    randombytes(sk+OSKR_SECRETKEYBYTES_MLKEM-OSKR_SYMBYTES, OSKR_SYMBYTES);//pos change (sk||pk||s):=sk
    return 0;
}

/*************************************************
* Name:        crypto_kem_enc
*
* Description: Generates cipher text and shared
*              secret for given public key
*
* Arguments:   - uint8_t *ct: pointer to output cipher text
*                (an already allocated array of OSKR_CIPHERTEXTBYTES bytes)
*              - uint8_t *ss: pointer to output shared secret
*                (an already allocated array of OSKR_SSBYTES bytes)
*              - const uint8_t *pk: pointer to input public key
*                (an already allocated array of OSKR_PUBLICKEYBYTES bytes)
*
* Returns 0 (success)
**************************************************/
int crypto_kem_enc_AKCN(unsigned char *ct, unsigned char *K, const unsigned char *pk)
{
    uint8_t buf[PREFIXLEN + OSKR_SYMBYTES];
    uint8_t kr[2*OSKR_SYMBYTES];

    randombytes(buf + PREFIXLEN, OSKR_SYMBYTES);// m
    memcpy(buf, pk, PREFIXLEN);// ID(pk)||m

    kdf(kr, buf, PREFIXLEN + OSKR_SYMBYTES);// G(ID(pk),m)->(K,r)
    indcpa_enc_AKCN(ct, buf + PREFIXLEN, pk, kr + OSKR_SYMBYTES);//CPAPKE.Enc(pk,m,r)->ct

    memcpy(K, kr, OSKR_SYMBYTES); // K
    return 0;
}

int crypto_kem_enc_mlkem(unsigned char *ct, unsigned char *K, const unsigned char *pk)
{
  uint8_t buf[2*OSKR_SYMBYTES];
  uint8_t kr[2*OSKR_SYMBYTES];

  randombytes(buf + OSKR_SYMBYTES, OSKR_SYMBYTES);// m
  hash_h(buf, pk, OSKR_INDCPA_PUBLICKEYBYTES);

  kdf(kr, buf, 2*OSKR_SYMBYTES);// G(H(pk),m)->(K,r)
  indcpa_enc_AKCN(ct, buf + OSKR_SYMBYTES, pk, kr + OSKR_SYMBYTES);//CPAPKE.Enc(pk,m,r)->ct

  memcpy(K, kr, OSKR_SYMBYTES);
  return 0;
}

int crypto_kem_enc_kyber(unsigned char *ct, unsigned char *K, const unsigned char *pk)
{
  uint8_t buf[2*OSKR_SYMBYTES];
  uint8_t kr[2*OSKR_SYMBYTES];

  randombytes(buf + OSKR_SYMBYTES, OSKR_SYMBYTES);// m
  hash_h(buf + OSKR_SYMBYTES, buf + OSKR_SYMBYTES, OSKR_SYMBYTES); //H(m)

  hash_h(buf, pk, OSKR_INDCPA_PUBLICKEYBYTES);

  kdf(kr, buf, 2*OSKR_SYMBYTES);// G(H(pk),m)->(K,r)
  indcpa_enc_AKCN(ct, buf + OSKR_SYMBYTES, pk, kr + OSKR_SYMBYTES);//CPAPKE.Enc(pk,m,r)->ct
  /* overwrite coins in kr with H(c) */
  hash_h(kr+OSKR_SYMBYTES, ct, OSKR_CIPHERTEXTBYTES);
  /* hash concatenation of pre-k and H(c) to k */
  kdf3(K, kr, 2*OSKR_SYMBYTES);
  return 0;
}

/*************************************************
* Name:        crypto_kem_dec
*
* Description: Generates shared secret for given
*              cipher text and private key
*
* Arguments:   - uint8_t *ss: pointer to output shared secret
*                (an already allocated array of OSKR_SSBYTES bytes)
*              - const uint8_t *ct: pointer to input cipher text
*                (an already allocated array of OSKR_CIPHERTEXTBYTES bytes)
*              - const uint8_t *sk: pointer to input private key
*                (an already allocated array of OSKR_SECRETKEYBYTES bytes)
*
* Returns 0.
*
* On failure, ss will contain a pseudo-random value.
**************************************************/
int crypto_kem_dec_AKCN(unsigned char *K, const unsigned char *ct, const unsigned char *sk)
{
    int fail;
    uint8_t buf[PREFIXLEN + OSKR_SYMBYTES];
    uint8_t kr[2*OSKR_SYMBYTES];
    uint8_t cmp[OSKR_CIPHERTEXTBYTES];
    uint8_t buf2[PREFIXLEN + OSKR_SYMBYTES+OSKR_CIPHERTEXTBYTES];
    const uint8_t *pk = sk + OSKR_INDCPA_SECRETKEYBYTES;

    indcpa_dec_AKCN(buf + PREFIXLEN, ct, sk); // m'
    memcpy(buf, pk, PREFIXLEN);// ID(pk)||m'

    kdf(kr, buf, PREFIXLEN + OSKR_SYMBYTES);//G(ID(pk)||m')->(K',r')
    indcpa_enc_AKCN(cmp, buf+PREFIXLEN, pk, kr + OSKR_SYMBYTES); // ct'
    fail = verify(ct, cmp, OSKR_CIPHERTEXTBYTES);

    memcpy(buf2, pk, PREFIXLEN);
    memcpy(buf2 + PREFIXLEN, sk + OSKR_INDCPA_SECRETKEYBYTES + OSKR_INDCPA_PUBLICKEYBYTES, OSKR_SYMBYTES);
    memcpy(buf2 + PREFIXLEN + OSKR_SYMBYTES, ct, OSKR_CIPHERTEXTBYTES);

    kdf1(K, buf2, PREFIXLEN + OSKR_SYMBYTES + OSKR_CIPHERTEXTBYTES);

    cmov(K,kr,OSKR_SYMBYTES,!fail);

    return 0;
}

int crypto_kem_dec_mlkem(unsigned char *K, const unsigned char *ct, const unsigned char *sk)
{
  int fail;
  uint8_t buf[2*OSKR_SYMBYTES];
  uint8_t buf2[OSKR_SYMBYTES+OSKR_CIPHERTEXTBYTES];
  uint8_t kr[2*OSKR_SYMBYTES];
  uint8_t cmp[OSKR_CIPHERTEXTBYTES];
  const uint8_t *pk = sk+OSKR_INDCPA_SECRETKEYBYTES;

  indcpa_dec_AKCN(buf + OSKR_SYMBYTES, ct, sk);
  memcpy(buf, sk+OSKR_SECRETKEYBYTES_MLKEM-2*OSKR_SYMBYTES, OSKR_SYMBYTES);
  
  kdf(kr, buf, 2*OSKR_SYMBYTES);
  indcpa_enc_AKCN(cmp, buf+OSKR_SYMBYTES, pk, kr+OSKR_SYMBYTES);
  fail = verify(ct, cmp, OSKR_CIPHERTEXTBYTES);

  /* Compute rejection key */
  //kdf2(K,sk+OSKR_SECRETKEYBYTES_MLKEM-OSKR_SYMBYTES,ct);
  memcpy(buf2, sk+OSKR_SECRETKEYBYTES_MLKEM-OSKR_SYMBYTES, OSKR_SYMBYTES);
  memcpy(buf2 + OSKR_SYMBYTES, ct, OSKR_CIPHERTEXTBYTES);
  kdf3(K, buf2, OSKR_SYMBYTES+OSKR_CIPHERTEXTBYTES);

  /* Copy true key to return buffer if fail is false */
  cmov(K,kr,OSKR_SYMBYTES,!fail);

  return 0;
}

int crypto_kem_dec_kyber(unsigned char *K, const unsigned char *ct, const unsigned char *sk)
{
  int fail;
  uint8_t buf[2*OSKR_SYMBYTES];
  uint8_t kr[2*OSKR_SYMBYTES];
  uint8_t cmp[OSKR_CIPHERTEXTBYTES];
  const uint8_t *pk = sk+OSKR_INDCPA_SECRETKEYBYTES;

  indcpa_dec_AKCN(buf + OSKR_SYMBYTES, ct, sk);
  memcpy(buf, sk+OSKR_SECRETKEYBYTES_MLKEM-2*OSKR_SYMBYTES, OSKR_SYMBYTES);
  
  kdf(kr, buf, 2*OSKR_SYMBYTES);
  indcpa_enc_AKCN(cmp, buf+OSKR_SYMBYTES, pk, kr+OSKR_SYMBYTES);
  fail = verify(ct, cmp, OSKR_CIPHERTEXTBYTES);

  hash_h(kr+OSKR_SYMBYTES, ct, OSKR_CIPHERTEXTBYTES);
  cmov(kr, sk+OSKR_SECRETKEYBYTES_MLKEM-OSKR_SYMBYTES, OSKR_SYMBYTES, fail);

  /* hash concatenation of pre-k and H(c) to k */
  kdf3(K, kr, 2*OSKR_SYMBYTES);

  return 0;
}