CC = gcc

ALL_EXAMPLES = ex01 ex02 ex03 ex04 ex05 ex06 ex07 ex08 ex09 ex10

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<

.PHONY: all clean


all: $(ALL_EXAMPLES)

clean:
	-rm -f *.o
	-rm -f $(ALL_EXAMPLES)

ex01: ex01.o
	$(CC) $(LDFLAGS) $^ -o $@
ex02: ex02.o
	$(CC) $(LDFLAGS) $^ -o $@
ex03: ex03.o 
	$(CC) $(LDFLAGS) $^ -o $@
ex04: ex04.o child_fn1.o
	$(CC) $(LDFLAGS) $^ -o $@
ex05: ex05.o child_fn1.o
	$(CC) $(LDFLAGS) $^ -o $@
ex06: ex06.o child_fn2.o
	$(CC) $(LDFLAGS) $^ -o $@
ex07: ex07.o child_fn2.o
	$(CC) $(LDFLAGS) $^ -o $@
ex08: ex08.o child_fn3.o mount_ns.o user_ns.o
	$(CC) $(LDFLAGS) $^ -o $@
ex09: ex09.o child_fn3.o mount_ns.o user_ns.o
	$(CC) $(LDFLAGS) $^ -o $@
ex10: ex10.o child_fn3.o mount_ns.o user_ns.o
	$(CC) $(LDFLAGS) $^ -o $@
