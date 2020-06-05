#ifndef __bignum__H__
#define __bignum__H__

#include <stdint.h>

#define BIGNUM_OK 0
#define BIGNUM_ZERODIV 1

void bignum_debug_buf(const char *name, uint8_t* data, uint16_t len);

uint8_t bignum_iszero(uint8_t *bignum, uint16_t len);

uint8_t bignum_lshift(uint8_t *bn, uint16_t bits, uint16_t len);

uint8_t bignum_bitget(uint8_t *bn, uint16_t bits, uint16_t len);
uint8_t bignum_bitset(uint8_t *bn, uint16_t bits, uint8_t val, uint16_t len);

int8_t bignum_compare(uint8_t *left, uint8_t *right, uint16_t len);

uint8_t bignum_add(uint8_t *dest, uint8_t *a, uint8_t *b, uint16_t len);
uint8_t bignum_sub(uint8_t *dest, uint8_t *a, uint8_t *b, uint16_t len);

uint8_t bignum_divmod(uint8_t *quotient, uint8_t *remainder,
                      uint8_t *dividend, uint8_t *divisor, uint16_t len);

#endif /* __BIGNUM__H__ */
