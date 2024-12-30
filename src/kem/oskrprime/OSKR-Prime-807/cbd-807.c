#include <stdint.h>
#include "params-807.h"
#include "cbd-807.h"

/*************************************************
* Name:        load24_littleendian
*
* Description: load 3 bytes into a 32-bit integer
*              in little-endian order.
*
* Arguments:   - const uint8_t *x: pointer to input byte array
*
* Returns 32-bit unsigned integer loaded from x (most significant byte is zero)
**************************************************/
static uint32_t load24_littleendian(const uint8_t x[3])
{
  uint32_t r;
  r  = (uint32_t)x[0];
  r |= (uint32_t)x[1] << 8;
  r |= (uint32_t)x[2] << 16;
  return r;
}

/*************************************************
* Name:        cbd3
*
* Description: Given an array of uniformly random bytes, compute
*              polynomial with coefficients distributed according to
*              a centered binomial distribution with parameter eta=4
*
* Arguments:   - poly *r: pointer to output polynomial
*              - const uint8_t *buf: pointer to input byte array
**************************************************/
void cbd3(poly *r, const uint8_t buf[202]) { //buf=67*3+1=202
    unsigned int i,j;
    uint32_t t,d;
    int16_t a,b;

    for(i = 0; i < OSKR_N/4; i++) { //268:r[0]~r[267]
      t  = load24_littleendian(buf + 3 * i);// 24b
      d  = t & 0x00249249;// 0b1001001001001001001001
      d += (t >> 1) & 0x00249249;//
      d += (t >> 2) & 0x00249249;//拼成3-bit的形式

      for(j = 0; j < 4; j++) {// 4 coeffs
        a = (d >> (6 * j + 0)) & 0x7;// low 3b
        b = (d >> (6 * j + 3)) & 0x7;
        r->coeffs[4 * i + j] = a - b;
      }
    }

    //1:r[268]
    t = buf[201];
    d  = t & 0x49; //0b01001001
    d += (t >> 1) & 0x49;
    d += (t >> 2) & 0x49;

    a = (d >> 0) & 0x7;
    b = (d >> 3) & 0x7;
    r->coeffs[268] = a - b;
}