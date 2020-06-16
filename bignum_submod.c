#include <stddef.h>
#include <stdbool.h>
#include <alloca.h>
#include <stdio.h>
#include "bignum.h"

uint8_t bignum_submod(uint8_t *dest, uint8_t *a, uint8_t *b, uint8_t *mod, uint16_t len)
  {
    uint8_t ret;

    //compute neg (mod p)
    uint8_t *neg = alloca(len);
    bignum_negmod(neg, b, mod, len);
    bignum_addmod(dest, a, neg, mod, len);
  }

