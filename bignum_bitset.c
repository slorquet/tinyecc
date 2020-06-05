#include "bignum.h"

uint8_t bignum_bitset(uint8_t *bn, uint16_t bit, uint8_t val, uint16_t len)
  {
    if(val)
      bn[bit>>3] |=   1<< (7-(bit&7)) ;
    else
      bn[bit>>3] &= ~(1<< (7-(bit&7)));
    return BIGNUM_OK;
  }

