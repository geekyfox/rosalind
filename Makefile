.phony: test memtest

OBJS = build/invoke.o 												\
	   $(foreach x, $(shell find src -name '*.c'), \
	                $(subst src,build,$(subst .c,.o,$(x))))

CFLAGS = -g -O2 -Wall

rosalind : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lm

build/invoke.c : utils/gen_invoke.c.sh src/rosalind.h
	@mkdir -p build
	$< > $@

build/invoke.o : build/invoke.c
	@mkdir -p build
	$(CC) $(CFLAGS) $< -c -o $@

build/%.o : src/%.c src/rosalind.h
	@mkdir -p build/solutions
	$(CC) $(CFLAGS) $< -c -o $@

test : rosalind
	@mkdir -p temp
	./rosalind test

memtest : rosalind
	valgrind --leak-check=full --show-leak-kinds=all --max-stackframe=20886568 ./rosalind test

clean:
	rm -f rosalind
	rm -rf build/*
