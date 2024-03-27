#include <stdlib.h>

#include <oqs/kem_fptru.h>

/*2024-3-27
功能:将fptru1277注册到结构体KEM中，并为其提供信息(包括名称、版本、长度等)和指针(密钥生成、封装和解封装)
*/
OQS_KEM *OQS_KEM_fptru_1277_new(void) {
    OQS_KEM *kem = malloc(sizeof(OQS_KEM));
    if(kem == NULL){
        return NULL;
    }
    kem->method_name = OQS_KEM_alg_fptru_1277;
    kem->alg_version = "https://github.com/Prime-KEM/FPTRU-KEM";
    
    kem->claimed_nist_level = 1;//TODO:修改NIST等级
    kem->ind_cca = true;


    kem->length_public_key = OQS_KEM_fptru_1277_length_public_key;
    kem->length_secret_key = OQS_KEM_fptru_1277_length_secret_key;
    kem->length_ciphertext = OQS_KEM_fptru_1277_length_ciphertext;
    kem->length_shared_secret = OQS_KEM_fptru_1277_length_shared_secret;


    kem->keypair = OQS_KEM_fptru_1277_keypair;
    kem->encaps = OQS_KEM_fptru_1277_encaps;
    kem->decaps = OQS_KEM_fptru_1277_decaps;

    return kem;
}

/*2024-1-23
调用在源码中已经实现的函数，来完成函数的封装
*/
extern int crypto_kem_keygen(unsigned char *pk, unsigned char *sk);
extern int crypto_kem_encaps(unsigned char *ct, unsigned char *k,const unsigned char *pk);
extern int crypto_kem_decaps(unsigned char *k,const unsigned char *ct,const unsigned char *sk);

OQS_API OQS_STATUS OQS_KEM_ctruprime_1277_keypair(uint8_t *public_key,uint8_t *secret_key) {
    return (OQS_STATUS) crypto_kem_keygen(public_key ,secret_key); //TODO:这里的强制类型转化可能会存在问题  根据虚拟机上的结果修改一下->经过测试，加不加的结果都是不匹配(sad)
}

OQS_API OQS_STATUS OQS_KEM_ctruprime_1277_encaps(uint8_t *ciphertext,uint8_t *shared_secret,const uint8_t *public_key) {
    return (OQS_STATUS) crypto_kem_encaps(ciphertext,shared_secret,public_key);
}

OQS_API OQS_STATUS OQS_KEM_ctruprime_1277_decaps(uint8_t *shared_secret,const uint8_t *ciphertext,const uint8_t *secret_key) {
    return (OQS_STATUS) crypto_kem_decaps(shared_secret ,ciphertext ,secret_key);
}
