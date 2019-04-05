.PHONY: test

topssed: src/main.c
	$(CC) -Wall -o topssed src/main.c

clean:
	rm topssed || true

test: topssed
	bats test/
