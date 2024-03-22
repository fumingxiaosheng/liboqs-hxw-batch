#ifndef OQS_KEM_CTRUPRIME_H
#define OQS_KEM_CTRUPRIME_H

#include <oqs/oqs.h>

#ifdef OQS_ENABLE_KEM_ctruprime_653
#define OQS_KEM_ctruprime_653_length_public_key 994
#define OQS_KEM_ctruprime_653_length_secret_key 1353
#define OQS_KEM_ctruprime_653_length_ciphertext 898
#define OQS_KEM_ctruprime_653_length_shared_secret 32
OQS_KEM * OQS_KEM_ctruprime_653_new(void); //TODO1:
OQS_API OQS_STATUS OQS_KEM_ctruprime_653_keypair(uint8_t *public_key,uint8_t *secret_key); //TODO2
OQS_API OQS_STATUS OQS_KEM_ctruprime_653_encaps(uint8_t *ciphertext,uint8_t *shared_secret,const uint8_t *public_key);//TODO3
OQS_API OQS_STATUS OQS_KEM_ctruprime_653_decaps(uint8_t *shared_secret,const uint8_t *ciphertext,const uint8_t *secret_key);//TODO4
#endif

#endif 