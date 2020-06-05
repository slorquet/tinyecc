#include "bignum.h"

uint8_t bignum_bitget(uint8_t *bn, uint16_t bits, uint16_t len)
  {
    return (bn[bits>>3] >> (7-(bits&7)) ) & 1;
  }

