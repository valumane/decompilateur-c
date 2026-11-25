CFLAGS = -std=c11 -Wall -Wextra

a.out: main.c lib.c lib.h Makefile
	$(CC) $(CFLAGS) main.c lib.c -o a.out
