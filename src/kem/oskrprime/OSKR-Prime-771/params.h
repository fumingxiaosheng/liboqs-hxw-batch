#ifndef PARAMS_H
#define PARAMS_H


#define OSKR_NAMESPACE(s) fdu_oskrprime761_ref_##s


#define q 3923
#define Q 3025153
#define OSKR_N 257   /* OSKR768 with 256-bit key */
#define OSKR_K 3
#define N_PRIME 576
#define OSKR_ETA1 2
#define OSKR_ETA2 2
#define DV 5
#define DU 11

#define OSKR_SYMBYTES  32  //  (32 * OSKR_N / 256)   /* size in bytes of hashes, and seeds */
#define OSKR_SSBYTES   32  //  (32 * OSKR_N / 256)   /* size in bytes of shared key */

/* length for poly */
#define OSKR_POLYBYTES		386
#define OSKR_POLYVECBYTES	(OSKR_K * OSKR_POLYBYTES)

/* length for secret key */
#define OSKR_SECRETBYTES    97
#define OSKR_SECRETVECBYTES	(OSKR_K * OSKR_SECRETBYTES)

/* length for poly v in ct */
#define OSKR_POLYCOMPRESSEDBYTES_CV 161

/* length for poly u.vec[i] and polyvec u in ct */
#define OSKR_POLYCOMPRESSEDBYTES_CU 354
#define OSKR_POLYVECCOMPRESSEDBYTES_CU (OSKR_K * OSKR_POLYCOMPRESSEDBYTES_CU)

/* B.W. for PKE */
#define OSKR_INDCPA_MSGBYTES       (OSKR_SYMBYTES)
#define OSKR_INDCPA_PUBLICKEYBYTES (OSKR_POLYVECBYTES + OSKR_SYMBYTES)
#define OSKR_INDCPA_SECRETKEYBYTES (OSKR_SECRETVECBYTES)
#define OSKR_INDCPA_CTBYTES        (OSKR_POLYVECCOMPRESSEDBYTES_CU + OSKR_POLYCOMPRESSEDBYTES_CV)

/* B.W. for KEM */
#define OSKR_PUBLICKEYBYTES  (OSKR_INDCPA_PUBLICKEYBYTES)
#define OSKR_SECRETKEYBYTES  (OSKR_INDCPA_SECRETKEYBYTES + OSKR_INDCPA_PUBLICKEYBYTES + OSKR_SYMBYTES)
#define OSKR_CIPHERTEXTBYTES (OSKR_INDCPA_CTBYTES)

#endif
