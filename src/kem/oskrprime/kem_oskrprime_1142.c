#include<stdlib.h>

#include <oqs/kem_oskrprime.h>

OQS_KEM *OQS_KEM_oskrprime_1142_new(void){
    OQS_KEM *kem = malloc(sizeof(OQS_KEM));
    if(kem == NULL){
        return NULL;
    }
    kem->method_name = OQS_KEM_alg_oskrprime_1142;
    kem->alg_version = "nothing";
    
    kem->claimed_nist_level = 1;//TODO:修改NIST等级
    kem->ind_cca = true;


    kem->length_public_key = OQS_KEM_oskrprime_1142_length_public_key;
    kem->length_secret_key = OQS_KEM_oskrprime_1142_length_secret_key;
    kem->length_ciphertext = OQS_KEM_oskrprime_1142_length_ciphertext;
    kem->length_shared_secret = OQS_KEM_oskrprime_1142_length_shared_secret;


    kem->keypair = OQS_KEM_oskrprime_1142_keypair;
    kem->encaps = OQS_KEM_oskrprime_1142_encaps;
    kem->decaps = OQS_KEM_oskrprime_1142_decaps;

    return kem;
}

extern int crypto_kem_keypair_AKCN(unsigned char *pk, unsigned char *sk);
extern int crypto_kem_enc_AKCN(unsigned char *ct, unsigned char *K, const unsigned char *pk);
extern int crypto_kem_dec_AKCN(unsigned char *K, const unsigned char *ct, const unsigned char *sk);

OQS_API OQS_STATUS OQS_KEM_oskrprime_1142_keypair(uint8_t *public_key,uint8_t *secret_key) {
    return (OQS_STATUS) crypto_kem_keypair_AKCN(public_key ,secret_key); //TODO:这里的强制类型转化可能会存在问题  根据虚拟机上的结果修改一下->经过测试，加不加的结果都是不匹配(sad)
}

OQS_API OQS_STATUS OQS_KEM_oskrprime_1142_encaps(uint8_t *ciphertext,uint8_t *shared_secret,const uint8_t *public_key) {
    return (OQS_STATUS) crypto_kem_enc_AKCN(ciphertext,shared_secret,public_key);
}

OQS_API OQS_STATUS OQS_KEM_oskrprime_1142_decaps(uint8_t *shared_secret,const uint8_t *ciphertext,const uint8_t *secret_key) {
    return (OQS_STATUS) crypto_kem_dec_AKCN(shared_secret ,ciphertext ,secret_key);
}