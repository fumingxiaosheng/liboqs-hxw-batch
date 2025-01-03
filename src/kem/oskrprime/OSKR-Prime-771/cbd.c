#include <stdint.h>
#include "params.h"
#include "cbd.h"

/*************************************************
* Name:        load32_littleendian
*
* Description: load 4 bytes into a 32-bit integer
*              in little-endian order
*
* Arguments:   - const uint8_t *x: pointer to input byte array
*
* Returns 32-bit unsigned integer loaded from x
**************************************************/
static uint32_t load32_littleendian(const uint8_t x[4]) {
    uint32_t r;
    r = (uint32_t) x[0];
    r |= (uint32_t) x[1] << 8;
    r |= (uint32_t) x[2] << 16;
    r |= (uint32_t) x[3] << 24;
    return r;
}

/*************************************************
* Name:        cbd2
*
* Description: Given an array of uniformly random bytes, compute
*              polynomial with coefficients distributed according to
*              a centered binomial distribution with parameter eta=2
*
* Arguments:   - poly *r: pointer to output polynomial
*              - const uint8_t *buf: pointer to input byte array
**************************************************/
void cbd2(poly *r, const uint8_t buf[129]) { //buf=32*4+1=129
    unsigned int i, j;
    uint32_t t, d;
    int16_t a, b;

    for (i = 0; i < OSKR_N / 8; i++) { //256:r[0]~r[255]
        t = load32_littleendian(buf + 4*i);
        d = t & 0x55555555;  //0b1010101010101010101010101010101
        d += (t >> 1) & 0x55555555;

        for (j = 0; j < 8; j++) {
            a = (d >> (4*j + 0)) & 0x3;
            b = (d >> (4*j + 2)) & 0x3;
            r->coeffs[8*i + j] = a - b;
        }
    }

    //1:r[256]
    t = buf[128];
    d  = t & 0x55; //0b1010101
    d += (t >> 1) & 0x55;

    a = (d >> 0) & 0x3;
    b = (d >> 2) & 0x3;
    r->coeffs[256] = a - b;
    
}