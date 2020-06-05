#include <stdint.h>
#include "bignum.h"

uint8_t bignum_lshift(uint8_t *bn, uint16_t bits, uint16_t len)
  {
    uint16_t i;

    /* shift whole bytes */
    while(bits > 8)
      {
        for(i = 0; i < len-1; i++)
          {
            bn[i] = bn[i+1];
          }
          bn[len-1] = 0;
        bits -= 8;
      }

    /* shift less than 8 remaining bits */
    bn[0] <<= bits;
    for(i = 1; i < len; i++)
      {
        bn[i-1] |= bn[i] >> (8-bits);
        bn[i] <<= bits;
      }
    return BIGNUM_OK;
  }

