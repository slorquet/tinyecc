#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bignum.h"
#include "tinyecc.h"

uint8_t tinyecc_keypair_gen(tinyecc_rand_f random,
                            struct tinyecc_pubkey_t *pub,
                            struct tinyecc_privkey_t *priv)
  {
    uint16_t bytes;
    //check params
    if(random==NULL || pub==NULL || priv==NULL) return TINYECC_E_NULL;

    //check pub and priv have the same curve
    if(pub->curve != priv->curve) return TINYECC_E_INVALID;

    srand(time(NULL));

    //number of bytes to store this much bits
    bytes = TINYECC_BYTES_FOR_BITS(pub->curve->bits);

    printf("keygen: getting a random privkey\n");
    do
      {
        //generate a random s
        random(priv->s, bytes);

        //verify it's not zero (extremely unlikely, RNG is broken)
        if(bignum_iszero(priv->s, bytes))
          {
            continue;
          }

        //verify it's lower than order (very unlikely)
        if(bignum_compare(priv->s, priv->curve->r, bytes) >= 0)
          {
            continue;
          }

        //since S is lower than order, we are sure it's a field element
        //so, no need to compute s = s mod r
      }
    while(0);

  tinyecc_curve_load(priv->s  , pub->curve->bits,
    "70246E29AFE14870E983A9F29C118B559D0AB85263EB920352A6E37CBCA1BF29");

    bignum_debug_buf("privkey: ", priv->s, bytes);

    //compute the public key (wx,wy) = (gx,gy) * s
    gfp_scalar_mult(&pub->key,
                    &pub->curve->g,
                    priv->s,
                    pub->curve);

    return TINYECC_E_OK;
  }

