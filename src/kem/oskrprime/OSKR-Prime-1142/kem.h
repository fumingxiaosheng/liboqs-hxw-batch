#ifndef KEM_H
#define KEM_H

#include <stdint.h>
#include "params.h"

//#define crypto_kem_keypair_AKCN OSKR_NAMESPACE(keypair_AKCN)
int crypto_kem_keypair_AKCN(unsigned char *pk, unsigned char *sk);

#define crypto_kem_keypair_mlkem OSKR_NAMESPACE(keypair_mlkem)
int crypto_kem_keypair_mlkem(unsigned char *pk, unsigned char *sk);

//#define crypto_kem_enc_AKCN OSKR_NAMESPACE(enc_AKCN)
int crypto_kem_enc_AKCN(unsigned char *ct, unsigned char *K, const unsigned char *pk);

#define crypto_kem_enc_mlkem OSKR_NAMESPACE(enc_mlkem)
int crypto_kem_enc_mlkem(unsigned char *ct, unsigned char *K, const unsigned char *pk);

#define crypto_kem_enc_kyber OSKR_NAMESPACE(enc_kyber)
int crypto_kem_enc_kyber(unsigned char *ct, unsigned char *K, const unsigned char *pk);

//#define crypto_kem_dec_AKCN OSKR_NAMESPACE(dec_AKCN)
int crypto_kem_dec_AKCN(unsigned char *K, const unsigned char *ct, const unsigned char *sk);

#define crypto_kem_dec_mlkem OSKR_NAMESPACE(dec_mlkem)
int crypto_kem_dec_mlkem(unsigned char *K, const unsigned char *ct, const unsigned char *sk);

#define crypto_kem_dec_kyber OSKR_NAMESPACE(dec_kyber)
int crypto_kem_dec_kyber(unsigned char *K, const unsigned char *ct, const unsigned char *sk);
#endif
