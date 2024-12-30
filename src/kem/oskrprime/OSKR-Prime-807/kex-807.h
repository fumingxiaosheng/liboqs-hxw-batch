#ifndef KEX_H
#define KEX_H

#include <stdint.h>
#include "params-807.h"

#define KEX_UAKE_SENDABYTES (OSKR_PUBLICKEYBYTES + OSKR_CIPHERTEXTBYTES)
#define KEX_UAKE_SENDBBYTES (OSKR_CIPHERTEXTBYTES)

#define KEX_AKE_SENDABYTES (OSKR_PUBLICKEYBYTES + OSKR_CIPHERTEXTBYTES)
#define KEX_AKE_SENDBBYTES (2*OSKR_CIPHERTEXTBYTES)

#define KEX_SSBYTES OSKR_SSBYTES

#define kex_uake_initA_AKCN OSKR_NAMESPACE(kex_uake_initA_AKCN)
void kex_uake_initA_AKCN(uint8_t *send, uint8_t *tk, uint8_t *sk, const uint8_t *pkb);
#define kex_uake_sharedB_AKCN OSKR_NAMESPACE(kex_uake_sharedB_AKCN)
void kex_uake_sharedB_AKCN(uint8_t *send, uint8_t *k, const uint8_t *recv, const uint8_t *skb);
#define kex_uake_sharedA_AKCN OSKR_NAMESPACE(kex_uake_sharedA_AKCN)
void kex_uake_sharedA_AKCN(uint8_t *k, const uint8_t *recv, const uint8_t *tk, const uint8_t *sk);

#define kex_ake_initA_AKCN OSKR_NAMESPACE(kex_ake_initA_AKCN)
void kex_ake_initA_AKCN(uint8_t *send, uint8_t *tk, uint8_t *sk, const uint8_t *pkb);
#define kex_ake_sharedB_AKCN OSKR_NAMESPACE(kex_ake_sharedB_AKCN)
void kex_ake_sharedB_AKCN(uint8_t *send, uint8_t *k, const uint8_t *recv, const uint8_t *skb, const uint8_t *pka);
#define kex_ake_sharedA_AKCN OSKR_NAMESPACE(kex_ake_sharedA_AKCN)
void kex_ake_sharedA_AKCN(uint8_t *k, const uint8_t *recv, const uint8_t *tk, const uint8_t *sk, const uint8_t *ska);

#endif
