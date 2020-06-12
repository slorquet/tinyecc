#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bignum.h"

uint8_t bignum_divmod(uint8_t *quotient /*Q*/, uint8_t *remainder /*R*/,
                      uint8_t *dividend /*N*/, uint8_t *divisor /*D*/,
                      uint16_t bytes)
{
  uint16_t n = bytes << 3;
  int16_t i;

  uint8_t *rem = alloca(bytes);

  /* if D == 0 then error(DivisionByZeroException) end */
  if (bignum_iszero(divisor, bytes))
    {
      printf("division by zero\n");
      return BIGNUM_ZERODIV;
    }

  //bignum_debug_buf("divmod_A ", dividend, bytes);
  //bignum_debug_buf("divmod_B ", divisor , bytes);

  /* Q := 0                 -- initialize quotient and remainder to zero */
  /* R := 0                     */
  /* for i = n-1...0 do     -- where n is number of bits in N*/
  /*   R := R << 1          -- left-shift R by 1 bit*/
  /*   R(0) := N(i)         -- set the lsb of R equal to bit i of the numerator*/
  /*   if R >= D then*/
  /*     R := R - D*/
  /*     Q(i) := 1*/
  /*   end*/          
  /* end*/

  if(quotient) memset(quotient, 0, bytes);
  memset(rem, 0, bytes);

  for (i = n-1; i >= 0; i -= 1)
    {
      uint8_t bit;
      bit = bignum_bitget(dividend, i, bytes);
//printf("divmod dividend bit #%d value %d\n",i, bit);

      bignum_lshift(rem, 1, bytes);
      bignum_bitset(rem, 0, bit, bytes);

  //bignum_debug_buf("remainder ", rem, bytes);
      if(bignum_compare(rem, divisor, bytes) >= 0)
        {
         bignum_sub(rem, rem, divisor, bytes);
         if(quotient) bignum_bitset(quotient, i, 1, bytes);
      }
    }
  //if(quotient) bignum_debug_buf("divmod_Q ", quotient, bytes);
  //bignum_debug_buf("divmod_R ", rem, bytes);

  memcpy(remainder, rem, bytes);
  return BIGNUM_OK;
}

