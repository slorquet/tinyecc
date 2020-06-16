#include <stdio.h>
#include <string.h>
#include <alloca.h>
#include "bignum.h"
#include "tinyecc.h"

uint8_t gfp_scalar_mult(struct tinyecc_point_t *s,
                        struct tinyecc_point_t *q,
                        uint8_t *k, struct tinyecc_wcurve_t* curve)
{
    int16_t bit;
    uint16_t bytes = TINYECC_BYTES_FOR_BITS(curve->bits);

    struct tinyecc_point_t neg;
    uint8_t *h,*tmp1,*tmp2;


    /* Alg: We perform successive additions and shifts.
     * Initialize accumulator to zero
     * Initialize increment to source
     * For each bit in scalar,
     *  only if bit is set, add the current increment to accumulator
     *  in all cases, double the increment.
     */

    //1. If n = 0 then output O and stop.
    if(bignum_iszero(k,bytes))
      {
        s->infinity = true;
        return TINYECC_E_INVALID;
      }

    if(q->infinity)
      {
      return TINYECC_E_INVALID;
      }

    tmp1 = alloca(bytes);
    tmp2 = alloca(bytes);

    //2. If n < 0 the set Q <- (–P) and k <- (–n), else set Q <- P and k <- n.
    //3. Let hl hl–1 ...h1 h0 be the binary representation of 3k, where the most significant bit hl is 1.
    h = alloca(bytes);
    memcpy(h, k, bytes);        //h contains k
    bignum_lshift(h, 1, bytes); //h contains 2k
    bignum_add(h, h,k, bytes);  //h contains 3k
    bignum_debug_buf("3k=",h,bytes);

    neg.infinity = false;
    neg.x = q->x;
    neg.y = alloca(bytes);
    bignum_negmod(neg.y, q->y, curve->prime, bytes);

    //5. Set S <- Q.
    memcpy(s->x, q->x, bytes);
    memcpy(s->y, q->y, bytes);
    s->infinity = false;

    //4. Let kl kl–1...k1 k0 be the binary representation of k.
    //6. For i from l – 1 downto 1 do
    for(bit=curve->bits-1; bit>0; bit--)
      {
        uint8_t hi,ki;

        //    Set S <- 2S.
        printf("bit %d doubling step\n", bit);
        gfp_point_add(s, s, s, curve, tmp1, tmp2); //double the increment
    
        hi = bignum_bitget(h,bit,bytes);
        ki = bignum_bitget(k,bit,bytes);
        printf("hi=%d ki=%d\n",hi,ki);
        //    If hi = 1 and ki = 0 then compute S <- S + Q.
        if(hi == 1 && ki == 0)
          {
            printf("doing S<-S+Q\n");
            gfp_point_add(s, s, q, curve, tmp1, tmp2); //accumulate the increments
          }

        //    If hi = 0 and ki = 1 then compute S <- S – Q.
        if(hi == 0 && ki == 1)
          {
            printf("doing S<-S-Q\n");
            gfp_point_add(s, s, &neg, curve, tmp1, tmp2); //accumulate the increments
          }
printf("\n");
      }

    //7. Output S.
    return BIGNUM_OK;
  }

