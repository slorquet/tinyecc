#include "tinyecc.h"

uint8_t tinyecc_curve_load(uint8_t *dest, uint16_t bits, const char * buf)
  {
    uint16_t bytes;
    uint16_t len=0;
    const char *ptr;

    /* checks */
    if(bits==0) return TINYECC_E_INVALID;
    if(buf==NULL) return TINYECC_E_NULL;

    /* compute len */
    ptr = buf;
    while(*ptr) ptr++;
    len = ptr - buf;

    /* number of bytes to store this much bits */
    bytes = TINYECC_BYTES_FOR_BITS(bits);

    return (tinyecc_hex2bin(dest, bytes, buf, len)==bytes)?TINYECC_E_OK:TINYECC_E_INVALID;
  }

