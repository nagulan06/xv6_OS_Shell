
all:
	(cd xv6 && make)

clean:
	(cd xv6 && make clean)

test: clean all
	perl test.pl

test_extra: clean all
	perl script.pl

qemu: all
	(cd xv6 && make qemu-nox)

.PHONY: all test clean qemu
