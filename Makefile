OBJS=bignum_iszero.o bignum_lshift.o
OBJS+=bignum_bitset.o bignum_bitget.o bignum_compare.o
OBJS+=bignum_add.o bignum_sub.o bignum_divmod.o
OBJS+=bignum_debug_buf.o

OBJS+= gfp_point_add.o gfp_scalar_mult.o

OBJS+=tinyecc_bin2hex.o tinyecc_hex2bin.o
OBJS+=tinyecc_curve_init.o tinyecc_curve_load.o tinyecc_debug_curve.o
OBJS+=tinyecc_keypair_init.o tinyecc_keypair_gen.o

CC=gcc -g
CFLAGS=-I.

test: $(OBJS) testmain.o
	$(CC) -o $@ $^

.PHONY: clean
clean:
	rm -f $(OBJS) testmain.o test

