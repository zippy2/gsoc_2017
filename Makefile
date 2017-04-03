CFLAGS=$(shell pkg-config --cflags libvirt) $(shell pkg-config --libs libvirt)
CFLAGS+=-O0 -ggdb -Wall

%: %.c
	gcc -o $@ $(CFLAGS) $<

all:

clean:
	rm -f `for i in *.c; do basename $$i .c; done`
