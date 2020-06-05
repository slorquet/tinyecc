#include "tinyecc.h"

uint8_t tinyecc_curve_init(struct tinyecc_wcurve_t * curve, uint16_t bits,
                           uint8_t *buf, uint16_t buflen)
{
    uint16_t bytes;
    if(buf==NULL) return TINYECC_E_NULL;

    //number of bytes to store this much bits
    bytes = TINYECC_BYTES_FOR_BITS(bits);

    //a curve has 6 elements
    if(buflen < (6*bytes)) {
        return TINYECC_E_NOMEM;
    }

    curve->bits = bits;
    curve->prime = buf; buf += bytes;
    curve->a = buf;     buf += bytes;
    curve->b = buf;     buf += bytes;
    curve->g.x = buf;   buf += bytes;
    curve->g.y = buf;   buf += bytes;
    curve->g.infinity = false;
    curve->r = buf;

	//printf("curve init: p@%p a@%p b@%p x@%p y@%p r@%p\n",curve->prime,curve->a,curve->b,curve->x,curve->y,curve->r);
    return TINYECC_E_OK;
}

