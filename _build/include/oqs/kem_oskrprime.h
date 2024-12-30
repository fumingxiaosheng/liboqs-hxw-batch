#ifndef OQS_KEM_OSKRPRIME_H
#define OQS_KEM_OSKRPRIME_H

#include <oqs/oqs.h>

#ifdef OQS_ENABLE_KEM_oskrprime_538
#define OQS_KEM_oskrprime_538_length_public_key 908
#define OQS_KEM_oskrprime_538_length_secret_key 1210
#define OQS_KEM_oskrprime_538_length_ciphertext 875
#define OQS_KEM_oskrprime_538_length_shared_secret 32
OQS_KEM * OQS_KEM_oskrprime_538_new(void); 
OQS_API OQS_STATUS OQS_KEM_oskrprime_538_keypair(uint8_t *public_key,uint8_t *secret_key); //TODO2
OQS_API OQS_STATUS OQS_KEM_oskrprime_538_encaps(uint8_t *ciphertext,uint8_t *shared_secret,const uint8_t *public_key);//TODO3
OQS_API OQS_STATUS OQS_KEM_oskrprime_538_decaps(uint8_t *shared_secret,const uint8_t *ciphertext,const uint8_t *secret_key);//TODO4
#endif

#ifdef OQS_ENABLE_KEM_oskrprime_807
#define OQS_KEM_oskrprime_807_length_public_key 1346
#define OQS_KEM_oskrprime_807_length_secret_key 1681
#define OQS_KEM_oskrprime_807_length_ciphertext 1245
#define OQS_KEM_oskrprime_807_length_shared_secret 32
OQS_KEM * OQS_KEM_oskrprime_807_new(void); 
OQS_API OQS_STATUS OQS_KEM_oskrprime_807_keypair(uint8_t *public_key,uint8_t *secret_key); //TODO2
OQS_API OQS_STATUS OQS_KEM_oskrprime_807_encaps(uint8_t *ciphertext,uint8_t *shared_secret,const uint8_t *public_key);//TODO3
OQS_API OQS_STATUS OQS_KEM_oskrprime_807_decaps(uint8_t *shared_secret,const uint8_t *ciphertext,const uint8_t *secret_key);//TODO4
#endif

// #ifdef OQS_ENABLE_KEM_oskrprime_1076
// #define OQS_KEM_oskrprime_1076_length_public_key 2067
// #define OQS_KEM_oskrprime_1076_length_secret_key 2738 
// #define OQS_KEM_oskrprime_1076_length_ciphertext 1597
// #define OQS_KEM_oskrprime_1076_length_shared_secret 32
// OQS_KEM * OQS_KEM_oskrprime_1076_new(void); 
// OQS_API OQS_STATUS OQS_KEM_oskrprime_1076_keypair(uint8_t *public_key,uint8_t *secret_key); //TODO2
// OQS_API OQS_STATUS OQS_KEM_oskrprime_1076_encaps(uint8_t *ciphertext,uint8_t *shared_secret,const uint8_t *public_key);//TODO3
// OQS_API OQS_STATUS OQS_KEM_oskrprime_1076_decaps(uint8_t *shared_secret,const uint8_t *ciphertext,const uint8_t *secret_key);//TODO4
// #endif

// #ifdef OQS_ENABLE_KEM_oskrprime_1142
// #define OQS_KEM_oskrprime_1142_length_public_key 2067
// #define OQS_KEM_oskrprime_1142_length_secret_key 2738 
// #define OQS_KEM_oskrprime_1142_length_ciphertext 1597
// #define OQS_KEM_oskrprime_1142_length_shared_secret 32
// OQS_KEM * OQS_KEM_oskrprime_1142_new(void); 
// OQS_API OQS_STATUS OQS_KEM_oskrprime_1142_keypair(uint8_t *public_key,uint8_t *secret_key); //TODO2
// OQS_API OQS_STATUS OQS_KEM_oskrprime_1142_encaps(uint8_t *ciphertext,uint8_t *shared_secret,const uint8_t *public_key);//TODO3
// OQS_API OQS_STATUS OQS_KEM_oskrprime_1142_decaps(uint8_t *shared_secret,const uint8_t *ciphertext,const uint8_t *secret_key);//TODO4
// #endif

#endif