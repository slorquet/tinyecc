#include <stddef.h>
#include <stdbool.h>
#include "bignum.h"

uint8_t bignum_addmod(uint8_t *dest, uint8_t *a, uint8_t *b, uint8_t *mod, uint16_t len)
  {
    uint8_t ret;
    bool carry = false;

//bignum_debug_buf("addmod a ", a, len);
//bignum_debug_buf("addmod b ", b, len);
    ret = bignum_add(dest, a, b, len);
    if(ret == BIGNUM_CARRY)
      {
        carry = true;
        ret = BIGNUM_OK;
      }

    if(ret != BIGNUM_OK) return ret;
//bignum_debug_buf("addmod sum ", dest, len);
//bignum_debug_buf("addmod mod ", mod, len);

    if(bignum_compare(dest, mod, len) >= 0 || carry)
      {
        bignum_sub(dest, dest, mod, len);
      }
//bignum_debug_buf("addmod res ", dest, len);
    return ret;
  }

