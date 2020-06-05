#include <stdio.h>
#include "bignum.h"

void bignum_debug_buf(const char *name, uint8_t* data, uint16_t len)
  {
    uint16_t i;
    printf("[%p] %s",data,name);
    for(i=0;i<len;i++)
      {
        printf("%02X",data[i]);
      }
    printf("\n");
  }

