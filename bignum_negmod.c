#include "bignum.h"
#include <stdio.h>

uint8_t bignum_negmod(uint8_t *dest, uint8_t *a, uint8_t *mod, uint16_t len)
  {
    bignum_neg(dest, a, len);
    //result of negate is a negative number, so we always need to add the modulo to turn it back in the range
    bignum_add(dest, dest, mod, len);
    return BIGNUM_OK;
  }
