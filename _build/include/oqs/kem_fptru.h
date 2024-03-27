#ifndef OQS_KEM_FPTRU_H
#define OQS_KEM_FPTRU_H

#include <oqs/oqs.h>

//TODO:这里的宏是否需要改成batch的？
#ifdef OQS_ENABLE_KEM_fptru_653
#define OQS_KEM_fptru_653_length_public_key 994
#define OQS_KEM_fptru_653_length_secret_key 1353
#define OQS_KEM_fptru_653_length_ciphertext 898
#define OQS_KEM_fptru_653_length_shared_secret 32
OQS_KEM * OQS_KEM_fptru_653_new(void); 
OQS_API OQS_STATUS OQS_KEM_fptru_653_keypair(uint8_t *public_key,uint8_t *secret_key); //TODO2
OQS_API OQS_STATUS OQS_KEM_fptru_653_encaps(uint8_t *ciphertext,uint8_t *shared_secret,const uint8_t *public_key);//TODO3
OQS_API OQS_STATUS OQS_KEM_fptru_653_decaps(uint8_t *shared_secret,const uint8_t *ciphertext,const uint8_t *secret_key);//TODO4
#endif

#ifdef OQS_ENABLE_KEM_fptru_761
#define OQS_KEM_fptru_761_length_public_key 1158
#define OQS_KEM_fptru_761_length_secret_key 1571
#define OQS_KEM_fptru_761_length_ciphertext 952
#define OQS_KEM_fptru_761_length_shared_secret 32
OQS_KEM * OQS_KEM_fptru_761_new(void); 
OQS_API OQS_STATUS OQS_KEM_fptru_761_keypair(uint8_t *public_key,uint8_t *secret_key); //TODO2
OQS_API OQS_STATUS OQS_KEM_fptru_761_encaps(uint8_t *ciphertext,uint8_t *shared_secret,const uint8_t *public_key);//TODO3
OQS_API OQS_STATUS OQS_KEM_fptru_761_decaps(uint8_t *shared_secret,const uint8_t *ciphertext,const uint8_t *secret_key);//TODO4
#endif

#ifdef OQS_ENABLE_KEM_fptru_1277
#define OQS_KEM_fptru_1277_length_public_key 2067
#define OQS_KEM_fptru_1277_length_secret_key 2738 
#define OQS_KEM_fptru_1277_length_ciphertext 1597
#define OQS_KEM_fptru_1277_length_shared_secret 32
OQS_KEM * OQS_KEM_fptru_1277_new(void); 
OQS_API OQS_STATUS OQS_KEM_fptru_1277_keypair(uint8_t *public_key,uint8_t *secret_key); //TODO2
OQS_API OQS_STATUS OQS_KEM_fptru_1277_encaps(uint8_t *ciphertext,uint8_t *shared_secret,const uint8_t *public_key);//TODO3
OQS_API OQS_STATUS OQS_KEM_fptru_1277_decaps(uint8_t *shared_secret,const uint8_t *ciphertext,const uint8_t *secret_key);//TODO4
#endif

#endif 