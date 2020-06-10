#include "bignum.h"
#include <stdio.h>

uint8_t bignum_add(uint8_t *dest, uint8_t *a, uint8_t *b, uint16_t len)
  {
    uint16_t acc;
    uint8_t aa,bb,dd;
    acc = 0;
    while(len)
      {
      aa = a[len-1];
      bb = b[len-1];
      acc = aa + bb + acc;
      dd = acc & 0xFF;
      acc = acc >> 8;
      dest[len-1] = dd;
      //printf("ADD len-1=%d a[len-1]=%02X b[len-1]=%02X res[len-1]=%02X CY=%d\n", len-1, aa, bb, dd, acc);
      len -= 1;
      }
    return BIGNUM_OK;
  }
