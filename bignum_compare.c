#include "bignum.h"

int8_t bignum_compare(uint8_t *left, uint8_t *right, uint16_t len)
  {
  uint16_t i;
  for(i=0;i<len;i++)
    {
      if(left[i] < right[i])
        return -1;
      if(left[i] > right[i])
        return +1;
      }
    return 0;
  }

