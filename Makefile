OBJS=bignum_iszero.o bignum_lshift.o
OBJS+=bignum_bitset.o bignum_bitget.o bignum_compare.o
OBJS+=bignum_neg.o bignum_add.o bignum_sub.o bignum_mul.o bignum_divmod.o
OBJS+=bignum_negmod.o bignum_addmod.o bignum_submod.o bignum_mulmod.o
OBJS+=bignum_extendedgcd.o bignum_modinverse.o
OBJS+=bignum_loaduint.o
OBJS+=bignum_debug_buf.o

OBJS+= gfp_point_add.o gfp_scalar_mult.o
OBJS+= gfp_debug_point.o

OBJS+=tinyecc_bin2hex.o tinyecc_hex2bin.o
OBJS+=tinyecc_curve_init.o tinyecc_curve_load.o tinyecc_debug_curve.o tinyecc_point_oncurve.o
OBJS+=tinyecc_keypair_init.o tinyecc_keypair_gen.o

CC=gcc -g
CFLAGS=-O3 -I.

test: $(OBJS) testmain.o
	$(CC) -o $@ $^

.PHONY: clean
clean:
	rm -f $(OBJS) testmain.o test

