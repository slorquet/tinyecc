#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "tinyecc.h"

//return random bytes
static void genrand(uint8_t * dest, uint16_t len)
  {
    do dest[--len] = random(); while(len);
  }

int main(int argc, char **argv)
{
  char     buffer[128];
  uint16_t res;
  uint8_t  r;

  uint8_t data[256];
  struct tinyecc_wcurve_t curve;
  struct tinyecc_pubkey_t pub;
  struct tinyecc_privkey_t priv;
  uint8_t store[128];

  uint8_t test[8]={0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF};

  //test bin to hex conversion with a short buffer
  res = tinyecc_bin2hex(buffer, 7, test, sizeof(test));
  buffer[res]=0;
  printf("bin2hex (  7 bytes buffer, 8 data bytes) : res=%d , %s\n", res, buffer);

  //correct buffer size
  res = tinyecc_bin2hex(buffer, sizeof(buffer), test, sizeof(test));
  buffer[res]=0;
  printf("bin2hex (100 bytes buffer, 8 data bytes) : res=%d, %s\n", res, buffer);

#if 0
  memset(test,0,8);
  test[7] = 0x01;
  for(r=0;r<64;r++)
    {
      memcpy(store, test, 8);
      bignum_lshift(store, r, 8);
      printf("shifts: %3d ", r); printf_hex(store, 8); printf("\r\n");
    }
#endif

  //test curve initialization from a NULL buffer pointer
  r = tinyecc_curve_init(&curve, 128, NULL, 128);
  printf("Init curve using a NULL buffer: %d (expected: %d)\n",r, TINYECC_E_NULL);

  //test curve initialization for zero bits
  r = tinyecc_curve_init(&curve, 0, NULL, 128);
  printf("Init curve using an invalid length: %d (expected: %d)\n",r, TINYECC_E_INVALID);

  //test curve initialization from a buffer that is too small
  r = tinyecc_curve_init(&curve, 128, data, 64);
  printf("Init curve using a 64-byte buffer: %d (expected: %d)\n",r, TINYECC_E_NOMEM);

#if 0
  //test curve initialization from a sufficient storage buffer
  r = tinyecc_curve_init(&curve, 128, data, 128);
  printf("Init curve using a 128-byte buffer (%p): %d (expected: %d)\n", data, r, TINYECC_E_OK);

  //load data from secp128r1
  r = tinyecc_curve_load(curve.prime, curve.bits, "FFFFFFFDFFFFFFFFFFFFFFFFFFFFFFFF");
  printf("load secp128r1.p: %d, expected %d\n", r, TINYECC_E_OK);
  r = tinyecc_curve_load(curve.a    , curve.bits, "FFFFFFFDFFFFFFFFFFFFFFFFFFFFFFFC");
  printf("load secp128r1.a: %d, expected %d\n", r, TINYECC_E_OK);
  r = tinyecc_curve_load(curve.b    , curve.bits, "E87579C11079F43DD824993C2CEE5ED3");
  printf("load secp128r1.b: %d, expected %d\n", r, TINYECC_E_OK);
  r = tinyecc_curve_load(curve.x    , curve.bits, "161FF7528B899B2D0C28607CA52C5B86");
  printf("load secp128r1.x: %d, expected %d\n", r, TINYECC_E_OK);
  r = tinyecc_curve_load(curve.y    , curve.bits, "CF5AC8395BAFEB13C02DA292DDED7A83");
  printf("load secp128r1.y: %d, expected %d\n", r, TINYECC_E_OK);
  r = tinyecc_curve_load(curve.r    , curve.bits, "FFFFFFFE0000000075A30D1B9038A115");
  printf("load secp128r1.r: %d, expected %d\n", r, TINYECC_E_OK);
#else
  //test curve initialization from a sufficient storage buffer
  r = tinyecc_curve_init(&curve, 256, data, 256);
  printf("Init curve using a 256-byte buffer (%p): %d (expected: %d)\n", data, r, TINYECC_E_OK);
  //load data from NIST P-256
  tinyecc_curve_load(curve.prime, curve.bits,
    "FFFFFFFF00000001000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFF");
  tinyecc_curve_load(curve.a    , curve.bits,
    "FFFFFFFF00000001000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFC");
  tinyecc_curve_load(curve.b    , curve.bits,
    "5AC635D8AA3A93E7B3EBBD55769886BC651D06B0CC53B0F63BCE3C3E27D2604B");
  tinyecc_curve_load(curve.g.x    , curve.bits,
    "6B17D1F2E12C4247F8BCE6E563A440F277037D812DEB33A0F4A13945D898C296");
  tinyecc_curve_load(curve.g.y    , curve.bits,
    "4FE342E2FE1A7F9B8EE7EB4A7C0F9E162BCE33576B315ECECBB6406837BF51F5");
  tinyecc_curve_load(curve.r    , curve.bits,
    "FFFFFFFF00000000FFFFFFFFFFFFFFFFBCE6FAADA7179E84F3B9CAC2FC632551");
#endif

  tinyecc_debug_curve(&curve);

  //key generation init; buffer too small
  r = tinyecc_keypair_init(&pub, &priv, &curve, store, 32);
  printf("Init keypair : %d (expected: %d)\n", r, TINYECC_E_NOMEM);

  //key generation init; ok
  r = tinyecc_keypair_init(&pub, &priv, &curve, store, sizeof(store));
  printf("Init keypair : %d (expected: %d)\n", r, TINYECC_E_OK);

  r = tinyecc_keypair_gen(genrand, &pub, &priv);
  printf("Gen keypair : %d (expected: %d)\n", r, TINYECC_E_OK);

  return 0;
}

