#include "bignum.h"

uint8_t bignum_bitset(uint8_t *bn, uint16_t bit, uint8_t val, uint16_t len)
  {
//printf("bitset index %d value %d\n", bit, val);
    if(val)
      bn[(len-1)-(bit>>3)] |=   1<< ((bit&7)) ;
    else
      bn[(len-1)-(bit>>3)] &= ~(1<< ((bit&7)));
    return BIGNUM_OK;
  }

