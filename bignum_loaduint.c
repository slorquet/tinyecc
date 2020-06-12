#include <string.h>
#include "bignum.h"

uint8_t bignum_loaduint(uint8_t *dest, uint16_t len, uint64_t value)
  {
    uint16_t i;
    memset(dest,0,len);
    for(i=0;i<8;i++)
      {
        if(len>i) dest[len-i-1] = value & 0xFF;
        value >>= 8;
      }
    return BIGNUM_OK;
  }

