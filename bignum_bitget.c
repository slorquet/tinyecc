#include "bignum.h"

uint8_t bignum_bitget(uint8_t *src, uint16_t bit, uint16_t len)
  {
    uint8_t byte = src[(len-1) - (bit>>3)];

//printf("bitget %d byte %02X\n", bit, byte);
    bit &= 7;
    byte >>= (bit);
    return byte & 1;
  }

