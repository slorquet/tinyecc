#include <alloca.h>
#include <string.h>
#include <stdio.h>
#include "bignum.h"

uint8_t bignum_mul(uint8_t *res, uint8_t *a, uint8_t *b, uint16_t len)
  {
    uint8_t *acc = alloca(2*len);
    uint8_t *inc = alloca(2*len);
    uint16_t bits = len << 3;
    uint16_t i;

    memset(acc, 0, 2*len);
    memset(inc, 0, 2*len);
    memcpy(inc+len, a, len);

    //bignum_debug_buf("mul a=",a,len);
    //bignum_debug_buf("mul b=",b,len);

    for(i=0;i<bits;i++)
      {
        //printf("bit #%d -> %d\n",i, bignum_bitget(b,i,len));
        //bignum_debug_buf("mul inc=",inc,2*len);
        if(bignum_bitget(b,i,len))
          {
            bignum_add(acc, acc, inc, 2*len);
            //bignum_debug_buf("mul acc=", acc, 2*len);
          }
        bignum_lshift(inc, 1, 2*len);
      }
    memcpy(res,acc,len*2);
    //bignum_debug_buf("mul res=", res, 2*len);
    return BIGNUM_OK;
  }

