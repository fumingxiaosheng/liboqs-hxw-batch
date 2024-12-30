CC ?= /usr/bin/cc
CFLAGS += -Wall -Wextra -Wpedantic -Wmissing-prototypes -Wredundant-decls \
  -Wshadow -Wpointer-arith -O3 -fomit-frame-pointer
NISTFLAGS += -Wno-unused-result -O3 -fomit-frame-pointer
RM = /bin/rm

SOURCES = kex.c kem.c indcpa.c polyvec.c poly.c ntt.c cbd.c reduce.c verify.c
SOURCESKECCAK = $(SOURCES) fips202.c symmetric-shake.c
HEADERS = params.h kex.h kem.h indcpa.h polyvec.h poly.h ntt.h cbd.h reduce.c verify.h symmetric.h
HEADERSKECCAK = $(HEADERS) fips202.h

.PHONY: all

all: \
  test/test_kyber \
  test/test_kex \
  test/test_vectors \
  test/test_speed


test/test_kyber: $(SOURCESKECCAK) $(HEADERSKECCAK) test/test_kyber.c randombytes.c
	$(CC) $(CFLAGS) -DOSKR_K=3 $(SOURCESKECCAK) randombytes.c test/test_kyber.c -o test_kyber

test/test_kex: $(SOURCESKECCAK) $(HEADERSKECCAK) test/test_kex.c randombytes.c
	$(CC) $(CFLAGS) -DOSKR_K=3 $(SOURCESKECCAK) randombytes.c test/test_kex.c -o test_kex

test/test_vectors: $(SOURCESKECCAK) $(HEADERSKECCAK) test/test_vectors.c
	$(CC) $(CFLAGS) -DOSKR_K=3 $(SOURCESKECCAK) test/test_vectors.c -o test_vectors

test/test_speed: $(SOURCESKECCAK) $(HEADERSKECCAK) test/test_speed.c test/cpucycles.h test/cpucycles.c test/speed_print.h test/speed_print.c randombytes.c poly_mul.h poly_mul.c
	$(CC) $(CFLAGS) -DOSKR_K=3 $(SOURCESKECCAK) randombytes.c poly_mul.c test/cpucycles.c test/speed_print.c test/test_speed.c -o test_speed


clean:
	-$(RM) -rf *.gcno *.gcda *.lcov *.o *.so
	-$(RM) -rf test_kyber
	-$(RM) -rf test_kex
	-$(RM) -rf test_vectors
	-$(RM) -rf test_speed