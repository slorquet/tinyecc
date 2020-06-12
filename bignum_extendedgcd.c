#include <alloca.h>
#include <string.h>
#include <stdio.h>
#include "bignum.h"

/* Implement extended euclidean algorithm. We find x and y so a * x + b * y = gcd(a,b)
 * if a and b are coprime, then gcd(a,b) = 1 and x is the modular inverse of a modulo b.
 * y is also the modular inverse of b modulo a.
 * This is the iterative method from wikipedia:
 * function extended_gcd(a, b)
 *     x := 0    lastx := 1
 *     y := 1    lasty := 0
 *     while b ≠ 0
 *         quotient := a div b
 *         (a, b) := (b, a mod b)
 *         (x, lastx) := (lastx - quotient*x, x)
 *         (y, lasty) := (lasty - quotient*y, y)       
 *     return (lastx, lasty)
 */
uint8_t bignum_extendedgcd(uint8_t *x, uint8_t *y, uint8_t *a, uint8_t *b, uint16_t len)
  {
    uint8_t *tmp,*sub;
    uint8_t *xx,*lastx,*yy,*lasty,*aa,*bb,*q,*r;
    int iters = 0;

    tmp = alloca(len*2);
    sub = alloca(len*2);

    xx = alloca(len);
    lastx = alloca(len);
    aa = alloca(len); //take copies
    bb = alloca(len);
    q = alloca(len);
    r = alloca(len);
    
    // x := 0    lastx := 1
    memset(xx,0,len);
    memset(lastx,0,len);
    lastx[len-1] = 1;

    // y := 1    lasty := 0
    if(y)
      {
        yy = alloca(len);
        memset(yy,0,len);
        yy[len-1] = 1;
        lasty = alloca(len);
        memset(lasty,0,len);
      }


    memcpy(aa,a,len);
    memcpy(bb,b,len);

    // while b ≠ 0
    while(!bignum_iszero(bb,len))
      {
        iters += 1;
        // quotient := a div b
        // (a, b) := (b, a mod b)
//bignum_debug_buf("gcd a=",aa,len);
//bignum_debug_buf("gcd b=",bb,len);
        bignum_divmod(q,r,aa,bb,len);
//bignum_debug_buf("gcd q=",q,len);
//bignum_debug_buf("gcd r=",r,len);
//bignum_debug_buf("gcd x=",xx,len);
//if(y)bignum_debug_buf("gcd y=",yy,len);
        memcpy(aa, bb, len);
        memcpy(bb, r , len);
        // (x, lastx) := (lastx - quotient*x, x)
        bignum_mul(tmp, q, xx, len);
//bignum_debug_buf("gcd tmp=",tmp,2*len);
        memset(sub,0,2*len);
        memcpy(sub+len,lastx,len);
        bignum_sub(tmp, sub, tmp, len*2);
        if(!bignum_iszero(sub,len)) printf("overflow_x\n");
        memcpy(lastx,sub+len,len);
        memcpy(lastx, xx, len);
        memcpy(xx, tmp+len, len);

        if(y)
          {
            // (y, lasty) := (lasty - quotient*y, y)
            bignum_mul(tmp, q, yy, len);
//bignum_debug_buf("gcd tmp=",tmp,2*len);
            memset(sub,0,2*len);
            memcpy(sub+len,lasty,len);
            bignum_sub(tmp, sub, tmp, len*2);
            if(!bignum_iszero(sub,len)) printf("overflow_y\n");
            memcpy(lasty,sub+len,len);
            memcpy(lasty, yy, len);
            memcpy(yy, tmp+len, len);
          }
      }
printf("gcd in %d iters\n", iters);

    memcpy(x,lastx,len);
    if(y) memcpy(y,lasty,len);
    return BIGNUM_OK;
  }

