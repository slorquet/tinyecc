#ifndef __tynyecc__H__
#define __tinyecc__H__

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/*============================================================================*/
/* CONSTANTS */
/*============================================================================*/

/*----------------------------------------------------------------------------*/
/*
 * error codes
 */
#define TINYECC_E_OK       0
#define TINYECC_E_INVALID  1
#define TINYECC_E_NOMEM    2
#define TINYECC_E_NULL     3
#define TINYECC_E_ZERO     4

#define TINYECC_BYTES_FOR_BITS(bits) ((((bits)-1) / 8) + 1)

/*============================================================================*/
/* TYPES */
/*============================================================================*/

/*----------------------------------------------------------------------------*/
/*
 * describe a Weierstrass Elliptic Curve over GF(p)
 * y^3 = x^2 + ax + b
 * used for most standard curves
 */
struct tinyecc_point_t
  {
    bool    infinity;
    uint8_t *x; //never null
    uint8_t *y; //never null
  };

struct tinyecc_wcurve_t
  {
    uint16_t                bits;
    uint8_t                *prime; //Field
    uint8_t                *a;     //Curve params
    uint8_t                *b;
    struct tinyecc_point_t  g; //base point
    uint8_t                *r;     //order of cyclic group
  };

/*----------------------------------------------------------------------------*/
/*
 * describe a public key, for verification
 * a public key is a point on a given curve
 * We can compute the public key by with W = curve->G * s
 */
struct tinyecc_pubkey_t
  {
    struct tinyecc_wcurve_t * curve;
    struct tinyecc_point_t    key;
  };

/*----------------------------------------------------------------------------*/
/*
 * describe a private key, for signature
 * a private key is a bignum between 0 and curve->r
 */
struct tinyecc_privkey_t
  {
    struct tinyecc_wcurve_t * curve;
    uint8_t *                 s;	
  };

/*============================================================================*/
/* CALLBACKS */
/*============================================================================*/

/*----------------------------------------------------------------------------*/
/*
 * callback to generate random bytes
 */
typedef void (*tinyecc_rand_f)(uint8_t * dest, uint16_t len);

/*============================================================================*/
/* FUNCTIONS */
/*============================================================================*/
void tinyecc_debug_curve(struct tinyecc_wcurve_t *curve);
void gfp_debug_point(const char *name, struct tinyecc_point_t* data, uint16_t bits);

/*----------------------------------------------------------------------------*/
/*
 * convert hex data from a buffer to a bytestring.
 * return the number of bytes stored
 */
uint16_t tinyecc_hex2bin(uint8_t * dest, uint16_t destroom,
                         const char * hex, uint16_t hexlen);

/*----------------------------------------------------------------------------*/
/*
 * convert a byte string to a hex buffer
 * this function does NOT add a final zero to the string!
 * return the number of chars stored
 */
uint16_t tinyecc_bin2hex(char * dest, uint16_t destroom,
                         uint8_t * bin, uint16_t binlen);

/*----------------------------------------------------------------------------*/
/*
 * init a curve structure
 * returns 0 if ok.
 */
uint8_t tinyecc_curve_init(struct tinyecc_wcurve_t * curve, uint16_t bits,
                           uint8_t *buf, uint16_t buflen);

/*----------------------------------------------------------------------------*/
/*
 * load hexadecimal data into a curve element
 * returns 0 if ok.
 */
uint8_t tinyecc_curve_load(uint8_t *dest, uint16_t bits, const char * buf);

/*----------------------------------------------------------------------------*/
/*
 * initialize a keypair with a buffer
 */
uint8_t tinyecc_keypair_init(struct tinyecc_pubkey_t *pub,
                             struct tinyecc_privkey_t *priv,
                             struct tinyecc_wcurve_t* curve,
                             uint8_t* store, uint16_t storelen);

/*----------------------------------------------------------------------------*/
/*
 * generate a keypair
 */
uint8_t tinyecc_keypair_gen(tinyecc_rand_f rand,
                            struct tinyecc_pubkey_t * pub,
                            struct tinyecc_privkey_t * priv);

/*----------------------------------------------------------------------------*/
/*
 * show curve params
 */
void tinyecc_curve_debug(struct tinyecc_wcurve_t *curve);

//

uint8_t gfp_point_add(struct tinyecc_point_t *dest,
                      struct tinyecc_point_t *a,
                      struct tinyecc_point_t *b,
                      struct tinyecc_wcurve_t *curve,
                      uint8_t *tmp1, uint8_t *tmp2);

uint8_t gfp_scalar_mult(struct tinyecc_point_t *dest,
                        struct tinyecc_point_t *src,
                        uint8_t *scalar,
                        struct tinyecc_wcurve_t *curve);

#endif /* __tinyecc__H__ */

