#	Italo Tobler Silva - nUSP 8551910
CFLAGS = -lm -g -Wall

all: aux main
	gcc -o program *.o $(CFLAGS)

aux:
	gcc $(CFLAGS) -c schema.c
	gcc $(CFLAGS) -c my_strings.c

main:
	gcc $(CFLAGS) -c main.c

clean:
	rm -f *.o
	rm -f program
	clear

run:
	./program

.zip:
	zip trabalho5.zip *.c *.h Makefile

debug: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./program < case1.in > test.out
	diff test.out case1.out
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./program < case2.in > test.out
	diff test.out case2.out
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./program < case3.in > test.out
	diff test.out case3.out
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./program < case4.in > test.out
	diff test.out case4.out
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./program < case5.in > test.out
	diff test.out case5.out
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./program < case6.in > test.out
	diff test.out case6.out
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./program < case7.in > test.out
	diff test.out case7.out
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./program < case8.in > test.out
	diff test.out case8.out
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./program < case9.in > test.out
	diff test.out case9.out
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./program < case10.in > test.out
	diff test.out case10.out
