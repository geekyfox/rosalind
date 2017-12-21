.phony: test memtest

OBJS = build/entrypoint.o \

CFLAGS = -g -O2 -Wall

rosalind : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

build/%.o : src/%.c src/rosalind.h
	@mkdir -p build
	$(CC) $(CFLAGS) $< -c -o $@

test : rosalind
	@mkdir -p temp
	./rosalind test

memtest : rosalind
	valgrind --leak-check=full --show-leak-kinds=all ./rosalind test

clean:
	rm -f rosalind
	rm -f build/*
