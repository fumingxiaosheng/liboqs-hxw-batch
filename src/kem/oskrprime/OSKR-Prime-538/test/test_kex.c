#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../kem.h"
#include "../kex.h"

int main(void) {
    uint8_t pkb[OSKR_PUBLICKEYBYTES];
    uint8_t skb[OSKR_SECRETKEYBYTES];

    uint8_t pka[OSKR_PUBLICKEYBYTES];
    uint8_t ska[OSKR_SECRETKEYBYTES];

    uint8_t eska[OSKR_SECRETKEYBYTES];

    uint8_t uake_senda[KEX_UAKE_SENDABYTES];
    uint8_t uake_sendb[KEX_UAKE_SENDBBYTES];

    uint8_t ake_senda[KEX_AKE_SENDABYTES];
    uint8_t ake_sendb[KEX_AKE_SENDBBYTES];

    uint8_t tk[KEX_SSBYTES];
    uint8_t ka[KEX_SSBYTES];
    uint8_t kb[KEX_SSBYTES];
    uint8_t zero[KEX_SSBYTES];
    int i;

    for (i = 0; i < KEX_SSBYTES; i++)
        zero[i] = 0;

    crypto_kem_keypair_AKCN(pkb, skb);// Generate static key for Bob

    crypto_kem_keypair_AKCN(pka, ska);// Generate static key for Alice


    // Perform unilaterally authenticated key exchange
    kex_uake_initA_AKCN(uake_senda, tk, eska, pkb);// Run by Alice
    kex_uake_sharedB_AKCN(uake_sendb, kb, uake_senda, skb);// Run by Bob
    kex_uake_sharedA_AKCN(ka, uake_sendb, tk, eska);// Run by Alice


    if (memcmp(ka, kb, KEX_SSBYTES))
        printf("Error in UAKE\n");   

    if (!memcmp(ka, zero, KEX_SSBYTES))
        printf("Error: UAKE produces zero key\n");

    // Perform mutually authenticated key exchange

    kex_ake_initA_AKCN(ake_senda, tk, eska, pkb);// Run by Alice
    kex_ake_sharedB_AKCN(ake_sendb, kb, ake_senda, skb, pka);// Run by Bob
    kex_ake_sharedA_AKCN(ka, ake_sendb, tk, eska, ska);// Run by Alice

    if (memcmp(ka, kb, KEX_SSBYTES))
        printf("Error in AKE\n");

    if (!memcmp(ka, zero, KEX_SSBYTES))
        printf("Error: AKE produces zero key\n");


    printf("KEX_UAKE_SENDABYTES: %d\n", KEX_UAKE_SENDABYTES);
    printf("KEX_UAKE_SENDBBYTES: %d\n", KEX_UAKE_SENDBBYTES);

    printf("KEX_AKE_SENDABYTES: %d\n", KEX_AKE_SENDABYTES);
    printf("KEX_AKE_SENDBBYTES: %d\n", KEX_AKE_SENDBBYTES);

    return 0;
}
