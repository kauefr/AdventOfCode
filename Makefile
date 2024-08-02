CFLAGS := -Wall -Wextra

AdventOfCode: src/main.c
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f AdventOfCode