#include <stdio.h>
#include "tinyecc.h"

// see P1363 page 128 (annex A, pdf page 54)
/*
 * Input:
     a prime p > 3;
     coefficients a, b for an elliptic curve E: y^2 = x^3 + ax + b modulo p;
     points P0 = (x0,y0) and P1 = (x1, y1) on E.
 * Output: the point P2 := P0 + P1.
 */
uint8_t gfp_point_add(struct tinyecc_point_t *dest,
                      struct tinyecc_point_t *a,
                      struct tinyecc_point_t *b,
                      uint16_t bits)
  {
    uint16_t bytes = TINYECC_BYTES_FOR_BITS(bits);
    //1. If P0 = O then output P2 <- P1 and stop
    if(a->infinity)
      {
      memcpy(dest, b, sizeof(struct tinyecc_point_t));
      return;
      }

    //A is not infinity
    //2. If P1 = O then output P2 <- P0 and stop
    if(b->infinity)
      {
      memcpy(dest, a, sizeof(struct tinyecc_point_t));
      return;
      }

    //neither A or B is infinity
    //Are the number similar so we have to perform doubling?
    //3. If x0 != x1 then
    if(bignum_compare(a->x, b->x, bytes) == 0 &&
       bignum_compare(a->y, b->y, bytes) == 0)
      {
        //Point doubling
        //4. If y0 != y1 then output P2 <- O and stop
        //5. If y1 = 0 then output P2 <- O and stop
        //6 Set l <- (3 x1^2 + a) / (2y1) mod p

      }
    else
      {
        //Normal addition
        //3.1 set l <- (y0 – y1) / (x0 – x1) mod p
        //3.2 go to step 7

      }
    //7. Set x2 <- l^2 – x0 – x1 mod p
    //8. Set y2 <- (x1 – x2) l – y1 mod p
    //9. Output P2 <- (x2, y2)
  }

