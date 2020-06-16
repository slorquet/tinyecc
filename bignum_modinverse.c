#include <stddef.h>
#include <stdio.h>
#include "bignum.h"

uint8_t bignum_modinverse(uint8_t *dest, uint8_t *src, uint8_t *mod, uint16_t len)
  {
    //bignum_debug_buf("modinverse mod=",mod,len);
    //bignum_debug_buf("modinverse in =",src,len);
    bignum_extendedgcd(dest,NULL,src,mod,len);
    //bignum_debug_buf("modinverse out=",dest,len);

    //if result is negative (MSB set) -> bring back into field
    if(dest[0] & 0x80)
      {
        //printf("modinv fix neg\n");
        bignum_add(dest, dest, mod, len);
      }

    return BIGNUM_OK;
  }

