#include <stdio.h>
#include <string.h>
#include <alloca.h>
#include "bignum.h"
#include "tinyecc.h"

uint8_t gfp_scalar_mult(struct tinyecc_point_t *dest,
                        struct tinyecc_point_t *src,
                        uint8_t *scalar, uint8_t* prime, uint16_t bits)
{
    int16_t bit;
    uint16_t bytes = TINYECC_BYTES_FOR_BITS(bits);

    struct tinyecc_point_t inc;

    /* Alg: We perform successive additions and shifts.
     * Initialize accumulator to zero
     * Initialize increment to source
     * For each bit in scalar,
     *  only if bit is set, add the current increment to accumulator
     *  in all cases, double the increment.
     */

    //init
    if(src->infinity)
      return TINYECC_E_INVALID;

    dest->infinity = true;

    inc.x = alloca(bytes);
    inc.y = alloca(bytes);
    inc.infinity = false;
    memcpy(inc.x,src->x,bytes);
    memcpy(inc.y,src->y,bytes);

    //1. If n = 0 then output O and stop.
    //2. If n < 0 the set Q <- (–P) and k <- (–n), else set Q <- P and k <- n.
    //3. Let hl hl–1 ...h1 h0 be the binary representation of 3k, where the most significant bit hl is 1.
    //4. Let kl kl–1...k1 k0 be the binary representation of k.
    //5. Set S <- Q.
    //6. For i from l – 1 downto 1 do
        //    Set S <- 2S.
        //    If hi = 1 and ki = 0 then compute S <- S + Q.
        //    If hi = 0 and ki = 1 then compute S <- S – Q.
    //7. Output S.

    for(bit=bits-1; bit>=0; bit--)
      {
        printf("for bit %d scalar value=%d\n", bit, bignum_bitget(scalar, bit, bytes));
        if(bignum_bitget(scalar,bit,bytes))
          {
            gfp_point_add(dest, dest, &inc, bits); //accumulate the increments
          }
        gfp_point_add(&inc, &inc, &inc, bits); //double the increment
      }
    return BIGNUM_OK;
  }
