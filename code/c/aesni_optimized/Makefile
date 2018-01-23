RM=rm -f
CFLAGS=-O3 -march=native -mtune=native -fomit-frame-pointer
SRCS=main.c haraka.c
OBJS=$(subst .c,.o,$(SRCS))
OUTFILE="haraka"

all: haraka

haraka: $(OBJS)
	$(CC) -o $(OUTFILE) $(OBJS) $(LDLIBS)

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) *~ .depend

include .depend
