#include <stdio.h>
#include <string.h>
#include <alloca.h>
#include "bignum.h"
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
                      struct tinyecc_wcurve_t *curve,
                      uint8_t *tmp1, uint8_t *tmp2)
  {
    uint16_t bytes = TINYECC_BYTES_FOR_BITS(curve->bits);

    gfp_debug_point("gfp_add A:",a,curve->bits);
    gfp_debug_point("gfp_add B:",b,curve->bits);
    //1. If P0 = O then output P2 <- P1 and stop
    if(a->infinity)
      {
      memcpy(dest, b, sizeof(struct tinyecc_point_t));
      printf("A is infinity -> return B\n");
      return TINYECC_E_OK;
      }

    //A is not infinity
    //2. If P1 = O then output P2 <- P0 and stop
    if(b->infinity)
      {
      memcpy(dest, a, sizeof(struct tinyecc_point_t));
      printf("A is infinity -> return B\n");
      return TINYECC_E_OK;
      }

    dest->infinity = false;
    uint8_t *dx = alloca(bytes);
    uint8_t *dy = alloca(bytes);

    //neither A or B is infinity
    //Are the number similar so we have to perform doubling?
    //3. If x0 == x1 then
    if(bignum_compare(a->x, b->x, bytes) != 0)
      {
        //Normal addition
//printf("A and B different -> addition\n");
        //3.1 set L <- (y0 – y1) / (x0 – x1) mod p
        bignum_submod(tmp1, a->y, b->y, curve->prime, bytes); //T1 <- y0 - y1
//bignum_debug_buf("delta_y ",tmp1, bytes);
        bignum_submod(tmp2, a->x, b->x, curve->prime, bytes); //T2 <- x0 - x1
//bignum_debug_buf("delta_x ",tmp2, bytes);
        bignum_modinverse(tmp2, tmp2, curve->prime, bytes);   //T2 <- modinverse(T2)
        bignum_mulmod(tmp1, tmp1, tmp2, curve->prime, bytes); //T1 <- T1 * T2
//bignum_debug_buf("lambda ",tmp1, bytes);
        //3.2 go to step 7
      }
    else
      {
        //Point doubling
        //4. If y0 != y1 then output P2 <- O and stop
        if(bignum_compare(a->y, b->y, bytes) != 0)
          {
            dest->infinity = true;
            return TINYECC_E_OK;
          }
        //5. If y1 = 0 then output P2 <- O and stop
        if(bignum_iszero(a->y, bytes))
          {
            dest->infinity = true;
            return TINYECC_E_OK;
          }
//        printf("A and B similar -> doubling\n");

        //6 Set L <- (3 x1^2 + a) / (2y1) mod p

        bignum_mulmod(tmp1, b->x, b->x, curve->prime, bytes);     //T1 <- x1 * x1
        bignum_loaduint(tmp2, bytes, 3);                          //T2 <- 3
        bignum_mulmod(tmp1, tmp1, tmp2, curve->prime, bytes);     //T1 <- T1 * T2
        bignum_addmod(tmp1, tmp1, curve->a, curve->prime, bytes); //T1 <- T1 + a
        bignum_loaduint(tmp2, bytes, 2);                          //T2 <- 2
        bignum_mulmod(tmp2, b->y, tmp2, curve->prime, bytes);     //T2 <- y1 * T2
        bignum_modinverse(tmp2, tmp2, curve->prime, bytes);       //T2 <- modinverse(T2)
        bignum_mulmod(tmp1, tmp1, tmp2, curve->prime, bytes);     //T1 <- T1 * T2
//bignum_debug_buf("lambda ",tmp1, bytes);
      }
    //7. Set x2 <- L^2 – x0 – x1 mod p

    bignum_mulmod(tmp2, tmp1, tmp1, curve->prime, bytes); //T2 <- T1 * T1
//bignum_debug_buf("x2a ",tmp2, bytes);
    bignum_submod(tmp2, tmp2, a->x, curve->prime, bytes); //T2 <- T2 - x0
//bignum_debug_buf("x2b ",tmp2, bytes);
    bignum_submod(dx, tmp2, b->x, curve->prime, bytes);   //x2 <- T2 - x1
//bignum_debug_buf("x2  ",dx, bytes);

    //8. Set y2 <- (x1 – x2) L – y1 mod p
    bignum_submod(tmp2, b->x, dx, curve->prime, bytes);     //T2 <- x1 - x2
//bignum_debug_buf("y2a ",tmp2, bytes);
    bignum_mulmod(tmp2, tmp2, tmp1, curve->prime, bytes);   //T2 <- T2 * T1
//bignum_debug_buf("y2b ",tmp2, bytes);
    bignum_submod(dy, tmp2, b->y, curve->prime, bytes);     //y2 <- T2 - y1
//bignum_debug_buf("y2  ",dy, bytes);

    //9. Output P2 <- (x2, y2)
    memcpy(dest->x, dx, bytes);
    memcpy(dest->y, dy, bytes);
    gfp_debug_point("gfp_add A+B:",dest,curve->bits);
  }

