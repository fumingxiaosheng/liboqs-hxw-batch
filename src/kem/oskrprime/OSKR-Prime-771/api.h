#ifndef API_H
#define API_H

#include <stdint.h>

fdu_oskrprime768_ref

#define fdu_oskrprime768_SECRETKEYBYTES 3204
#define fdu_oskrprime768_PUBLICKEYBYTES 1634
#define fdu_oskrprime768_CIPHERTEXTBYTES 1767
#define fdu_oskrprime768_BYTES 32

#define fdu_oskrprime768_ref_SECRETKEYBYTES fdu_oskrprime768_SECRETKEYBYTES
#define fdu_oskrprime768_ref_PUBLICKEYBYTES fdu_oskrprime768_PUBLICKEYBYTES
#define fdu_oskrprime768_ref_CIPHERTEXTBYTES fdu_oskrprime768_CIPHERTEXTBYTES
#define fdu_oskrprime768_ref_BYTES fdu_oskrprime768_BYTES

int fdu_oskrprime768_ref_keypair(unsigned char *pk, unsigned char *sk);
int fdu_oskrprime768_ref_enc(unsigned char *ct, unsigned char *K, const unsigned char *pk);
int fdu_oskrprime768_ref_dec(unsigned char *K, const unsigned char *ct, const unsigned char *sk);

#endif
