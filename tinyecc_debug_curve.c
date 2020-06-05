#include <stdio.h>
#include "bignum.h"
#include "tinyecc.h"

void tinyecc_debug_curve(struct tinyecc_wcurve_t *curve)
  {
    uint16_t bytes = TINYECC_BYTES_FOR_BITS(curve->bits);
    printf("Curve parameters, bits=%d (bignumlen=%d)\n", curve->bits, bytes);
    bignum_debug_buf("P=", curve->prime , bytes);
    bignum_debug_buf("A=", curve->a     , bytes);
    bignum_debug_buf("B=", curve->b     , bytes);
    bignum_debug_buf("X=", curve->x     , bytes);
    bignum_debug_buf("Y=", curve->y     , bytes);
    bignum_debug_buf("R=", curve->r     , bytes);
  }

