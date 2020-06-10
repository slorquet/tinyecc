#include <stdio.h>
#include "bignum.h"
#include "tinyecc.h"

void gfp_debug_point(const char *name, struct tinyecc_point_t* data, uint16_t bits)
  {
    uint16_t i;
    uint16_t bytes = TINYECC_BYTES_FOR_BITS(bits);
    printf("[%p] %s ",data,name);
    if(data->infinity)
      {
        printf("<infinity> px=%p py=%p\n",data->x, data->y);
        return;
      }
    printf("X=");
    for(i=0;i<bytes;i++)
      {
        printf("%02X",data->x[i]);
      }
    printf(" Y=");
    for(i=0;i<bytes;i++)
      {
        printf("%02X",data->y[i]);
      }
    printf("\n");
  }

