#include <stddef.h>
#include "bignum.h"

uint8_t bignum_modinverse(uint8_t *dest, uint8_t *src, uint8_t *mod, uint16_t len)
  {
    bignum_debug_buf("modinverse mod=",mod,len);
    bignum_debug_buf("modinverse in =",src,len);
    bignum_extendedgcd(dest,NULL,src,mod,len);
    bignum_debug_buf("modinverse out=",dest,len);

    return BIGNUM_OK;
  }

