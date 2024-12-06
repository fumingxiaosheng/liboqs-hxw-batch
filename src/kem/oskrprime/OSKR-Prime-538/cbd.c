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
* Name:        cbd4
*
* Description: Given an array of uniformly random bytes, compute
*              polynomial with coefficients distributed according to
*              a centered binomial distribution with parameter eta=4
*
* Arguments:   - poly *r: pointer to output polynomial
*              - const uint8_t *buf: pointer to input byte array
**************************************************/
void cbd4(poly *r, const uint8_t buf[269]){ //67*4+1=269
    unsigned int i,j;
    uint32_t t,d;
    int16_t a,b;

    for(i = 0; i < OSKR_N/4; i++){ //268:r[0]~r[267]
      t = load32_littleendian(buf + 4 * i);
      d  = t & 0x11111111;// 0b10001000100010001000100010001
      d += (t >> 1) & 0x11111111;
      d += (t >> 2) & 0x11111111;
      d += (t >> 3) & 0x11111111;

      for(j = 0; j < 4; j++) {// 4 coeffs
        a = (d >> (8 * j + 0)) & 15;// low 4b
        b = (d >> (8 * j + 4)) & 15;
        r->coeffs[4 * i + j] = a - b;
      }
    }
    //1:r[268]
    t = buf[268];
    d  = t & 0x11; //0b10001
    d += (t >> 1) & 0x11;
    d += (t >> 2) & 0x11;
    d += (t >> 3) & 0x11;

    a = (d >> 0) & 15;
    b = (d >> 4) & 15;
    r->coeffs[268] = a - b;
}