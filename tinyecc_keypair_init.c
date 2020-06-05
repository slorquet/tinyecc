#include "tinyecc.h"

uint8_t tinyecc_keypair_init(struct tinyecc_pubkey_t *pub,
                           struct tinyecc_privkey_t *priv,
                           struct tinyecc_wcurve_t* curve,
                           uint8_t* store, uint16_t storelen)
  {
    uint16_t bytes;
    if(store==NULL) return TINYECC_E_NULL;

    //number of bytes to store this much bits
    bytes = TINYECC_BYTES_FOR_BITS(curve->bits);

    //a keypair has 3 elements: s (priv) wx (pub) wy (pub)
    if(storelen < (3*bytes))
      {
        return TINYECC_E_NOMEM;
      }

    priv->curve        = curve;
    priv->s            = store; store += bytes;

    pub->curve        = curve;
    pub->key.infinity = true;
    pub->key.x        = store; store += bytes;
    pub->key.y        = store;

    return TINYECC_E_OK;
}

