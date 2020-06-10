#include "bignum.h"
#include <stdio.h>

uint8_t bignum_sub(uint8_t *dest, uint8_t *a, uint8_t *b, uint16_t len)
  {
    //a - b = a + twoscomplement(b) = a + (b xor FF) + 1
    uint16_t acc;
    uint8_t aa,bb,dd;

    acc = 1;
    while(len)
      {
      aa = a[len-1];
      bb = b[len-1];
      acc = aa + (bb^0xFF) + acc;
      dd = acc & 0xFF;
      acc = acc >> 8;
      dest[len-1] = dd;
      //printf("SUB len-1=%d a[len-1]=%02X b[len-1]=%02X res[len-1]=%02X CY=%d\n", len-1, aa, bb, dd, acc);
      len -= 1;
      }
    return BIGNUM_OK;
  }
