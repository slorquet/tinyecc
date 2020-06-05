#include <stdint.h>
#include <stdbool.h>

bool bignum_iszero(uint8_t *bignum, uint16_t len)
  {
    uint16_t i;
    uint8_t  nz;

    nz = 0x00;
    for(i=0;i<len;i++) {
        nz |= bignum[i];
    }
    return !nz;
}

