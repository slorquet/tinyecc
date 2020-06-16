#include <alloca.h>
#include <string.h>
#include <stdio.h>
#include "bignum.h"

uint8_t bignum_mulmod(uint8_t *dest, uint8_t *a, uint8_t *b, uint8_t *mod, uint16_t len)
  {
#if 0
    uint8_t *acc = alloca(len);
    uint8_t *inc = alloca(len);
    uint16_t bits = len << 3;
    uint16_t i;

    memset(acc, 0, len);
    memcpy(inc, a, len);

    bignum_debug_buf("mulmod a=",a,len);
    bignum_debug_buf("mulmod b=",b,len);
    bignum_debug_buf("mulmod p=",mod,len);

    for(i=0;i<bits;i++)
      {
        printf("bit #%d -> %d\n",i, bignum_bitget(b,i,len));
        bignum_debug_buf("inc=",inc,len);
        if(bignum_bitget(b,i,len))
          {
            bignum_addmod(acc, acc, inc, mod, len);
            bignum_debug_buf("acc=", acc, len);
          }
        bignum_lshift(inc, 1, len);
        //bignum_addmod(inc, inc, inc, mod, len);
      }
    memcpy(dest,acc,len);
    bignum_debug_buf("res=", dest, len);
#else
    uint8_t *tmp = alloca(2*len);
    uint8_t *bigmod = alloca(2*len);

    memset(bigmod, 0, 2*len);
    memcpy(bigmod+len, mod, len);

    bignum_mul(tmp, a, b, len);
    bignum_divmod(NULL, tmp, tmp, bigmod, 2*len);
    memcpy(dest, tmp+len, len);
#endif
    return BIGNUM_OK;
  }

