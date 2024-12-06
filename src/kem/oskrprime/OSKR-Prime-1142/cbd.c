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
* Name:        load16_littleendian
*
* Description: load 2 bytes into a 32-bit integer
*              in little-endian order.
*
* Arguments:   - const uint8_t *x: pointer to input byte array
*
* Returns 32-bit unsigned integer loaded from x (most significant byte is zero)
**************************************************/
static uint32_t load16_littleendian(const uint8_t x[2])
{
  uint32_t r;
  r  = (uint32_t)x[0];
  r |= (uint32_t)x[1] << 8;
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
void cbd2(poly *r, const uint8_t buf[286]) { //buf=71*4+2=286
    unsigned int i, j;
    uint32_t t, d;
    int16_t a, b;

    for (i = 0; i < OSKR_N / 8; i++) { //568:r[0]~r[567]
        t = load32_littleendian(buf + 4 * i);
        d = t & 0x55555555;  //0b1010101010101010101010101010101
        d += (t >> 1) & 0x55555555;

        for (j = 0; j < 8; j++) {
            a = (d >> (4 * j + 0)) & 0x3;
            b = (d >> (4 * j + 2)) & 0x3;
            r->coeffs[8 * i + j] = a - b;
        }
    }

    //3:r[568]~r[570]
    t = load16_littleendian(buf+4*65);
    d  = t & 0x555555; //0b10101010101010101010101
    d += (t >> 1) & 0x555555;

    for(j = 0;j < 3;j++)
    {
        a = (d >> (4 * j + 0)) & 0x3;
        b = (d >> (4 * j + 2)) & 0x3;
        r->coeffs[568 + j] = a - b;
    }
}