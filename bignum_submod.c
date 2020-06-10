#include <stddef.h>
#include "bignum.h"

uint8_t bignum_submod(uint8_t *dest, uint8_t *a, uint8_t *b, uint8_t *mod, uint16_t len)
  {
    uint8_t ret;

    ret = bignum_sub(dest, a, b, len);
    if(ret != BIGNUM_OK) return ret;

    ret = bignum_divmod(NULL, dest, dest, mod, len);
    return ret;
  }

