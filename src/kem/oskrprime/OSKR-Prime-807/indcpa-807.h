#ifndef INDCPA_H
#define INDCPA_H

#include <stdint.h>
#include "params-807.h"
#include "polyvec-807.h"

#define indcpa_keypair OSKR_NAMESPACE(indcpa_keypair)
void indcpa_keypair(uint8_t pk[OSKR_INDCPA_PUBLICKEYBYTES],
                    uint8_t sk[OSKR_INDCPA_SECRETKEYBYTES]);

#define indcpa_enc_AKCN OSKR_NAMESPACE(indcpa_enc_AKCN)
void indcpa_enc_AKCN(uint8_t c[OSKR_INDCPA_CTBYTES],
                     const uint8_t m[OSKR_INDCPA_MSGBYTES],
                     const uint8_t pk[OSKR_INDCPA_PUBLICKEYBYTES],
                     const uint8_t coins[OSKR_SYMBYTES]);
/*
#define indcpa_enc_kyber OSKR_NAMESPACE(indcpa_enc_kyber)
void indcpa_enc_kyber(uint8_t c[OSKR_INDCPA_CTBYTES],
                      const uint8_t m[OSKR_INDCPA_MSGBYTES],
                      const uint8_t pk[OSKR_INDCPA_PUBLICKEYBYTES],
                      const uint8_t coins[OSKR_SYMBYTES]);
*/
#define indcpa_dec_AKCN OSKR_NAMESPACE(indcpa_dec_AKCN)
void indcpa_dec_AKCN(uint8_t m[OSKR_INDCPA_MSGBYTES],
                     const uint8_t c[OSKR_INDCPA_CTBYTES],
                     const uint8_t sk[OSKR_INDCPA_SECRETKEYBYTES]);
/*
#define indcpa_dec_kyber OSKR_NAMESPACE(indcpa_dec_kyber)
void indcpa_dec_kyber(uint8_t m[OSKR_INDCPA_MSGBYTES],
                      const uint8_t c[OSKR_INDCPA_CTBYTES],
                      const uint8_t sk[OSKR_INDCPA_SECRETKEYBYTES]);
*/
#endif
