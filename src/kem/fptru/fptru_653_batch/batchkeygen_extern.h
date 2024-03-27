#ifndef batchkeygen_extern_H
#define batchkeygen_extern_H

void keygen_batchtest();

#define crypto_core_mult3 crypto_core_mult3sntrup761
#define crypto_core_mult3sntrup761 crypto_core_mult3sntrup761_ref
extern int crypto_core_mult3sntrup761_ref(unsigned char *,const unsigned char *,const unsigned char *,const unsigned char *);


#define crypto_core_inv3 crypto_core_inv3sntrup761
#define crypto_core_inv3sntrup761 crypto_core_inv3sntrup761_ref
extern int crypto_core_inv3sntrup761_ref(unsigned char *,const unsigned char *,const unsigned char *,const unsigned char *);

#endif