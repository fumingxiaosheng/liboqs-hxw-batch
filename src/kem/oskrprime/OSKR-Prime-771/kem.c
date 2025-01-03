#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "params.h"
#include "kem.h"
#include "indcpa.h"
#include "verify.h"
#include "symmetric.h"
#include "randombytes.h"

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
int crypto_kem_keypair(unsigned char *pk, unsigned char *sk)
{
    indcpa_keypair(pk, sk);//CPAPKE's pk sk
    memcpy(sk + OSKR_INDCPA_SECRETKEYBYTES, pk, OSKR_INDCPA_PUBLICKEYBYTES);//pos change (sk||pk)
    randombytes(sk + OSKR_INDCPA_SECRETKEYBYTES + OSKR_INDCPA_PUBLICKEYBYTES, OSKR_SYMBYTES);//pos change (sk||pk||s):=sk
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

    randombytes(buf + PREFIXLEN, OSKR_SYMBYTES);//m
    memcpy(buf, pk, PREFIXLEN);// ID(pk)||m

    kdf(kr, buf, PREFIXLEN + OSKR_SYMBYTES);// G(ID(pk),m)->(K,r)
    indcpa_enc_AKCN(ct, buf + PREFIXLEN, pk, kr + OSKR_SYMBYTES);//CPAPKE.Enc(pk,m,r)->ct

    memcpy(K, kr, OSKR_SYMBYTES);// K
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

