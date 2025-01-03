#ifndef KEM_H
#define KEM_H

#include <stdint.h>
#include "params.h"

//#define crypto_kem_keypair OSKR_NAMESPACE(keypair_AKCN)
int crypto_kem_keypair(unsigned char *pk, unsigned char *sk);

//#define crypto_kem_enc_AKCN OSKR_NAMESPACE(enc_AKCN)
int crypto_kem_enc_AKCN(unsigned char *ct, unsigned char *K, const unsigned char *pk);

//#define crypto_kem_dec_AKCN OSKR_NAMESPACE(dec_AKCN)
int crypto_kem_dec_AKCN(unsigned char *K, const unsigned char *ct, const unsigned char *sk);

#endif
