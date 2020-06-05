#include <stdio.h>
#include "tinyecc.h"


uint16_t tinyecc_bin2hex(char * dest, uint16_t destroom, uint8_t *bin, uint16_t binlen)
  {
    static const char hex[17]="0123456789ABCDEF";
    if(dest==NULL || bin==NULL || destroom==0 || binlen==0)
      {
        return 0;
      }

    //convert
    uint16_t idx=0;
    while(idx<binlen)
      {
        if(destroom<2) break;
        dest[(idx<<1)  ]=hex[(*bin)>>4];
        dest[(idx<<1)+1]=hex[(*bin)&15];
        destroom -= 2;
        bin++;
        idx++;
      }
    return (idx<<1);
  }

