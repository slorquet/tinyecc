#include <alloca.h>
#include "tinyecc.h"
#include "bignum.h"

//point is on curve if elliptic equation is verified,
//eg y^2 = x^3 + ax +b [mod p]
bool tinyecc_point_oncurve(struct tinyecc_wcurve_t *curve, struct tinyecc_point_t *point)
  {
  uint16_t len = curve->bits >> 3;

  uint8_t *left = alloca(len);
  bignum_mulmod(left, point->y, point->y, curve->prime, len);  // L = Y * Y

  uint8_t *right = alloca(len);
  bignum_mulmod(right, point->x, point->x, curve->prime, len); // R = X * X
  bignum_mulmod(right, right   , point->x, curve->prime, len); // R = R * X = X^3

  uint8_t *tmp = alloca(len);
  bignum_mulmod(tmp, curve->a, point->x, curve->prime, len);   // T = AX

  bignum_addmod(right, right, tmp, curve->prime, len);         // R = R + T = X^3 + AX
  bignum_addmod(right, right, curve->b, curve->prime, len);    // R = R + B = X^3 + AX + B
    
  return bignum_compare(left, right, len) == 0;
  }

