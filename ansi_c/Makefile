CC=gcc
CFLAGS=-Wall -g

clean:
	rm -f ex1
	rm -f ex3
	rm -f ex6
	rm -f ex7
	rm -f ex8
	rm -f ex9
	rm -f ex10
	rm -f ex11
	rm -f ex14
	rm -f ex15
	rm -f ex16
	rm -f ex16_ec
	rm -f ex17

all: 
	make clean
	make ex1
	make ex3
	make ex6
	make ex7
	make ex8
	make ex9
	make ex10
	make ex11
	make ex14
	make ex15
	make ex16
	make ex16_ec
	make ex17

test:
	valgrind ./ex1 --log-file=ex1_log.txt
	valgrind ./ex3 --log-file=ex3_log.txt
	valgrind ./ex6 --log-file=ex6_log.txt
	valgrind ./ex7 --log-file=ex7_log.txt
	valgrind ./ex8 --log-file=ex8_log.txt
	valgrind ./ex9 --log-file=ex9_log.txt
	valgrind ./ex10 --log-file=ex10_log.txt
	valgrind ./ex11 --log-file=ex11_log.txt
	valgrind ./ex14 --log-file=ex14_log.txt
	valgrind ./ex15 --log-file=ex15_log.txt
	valgrind ./ex16 --log-file=ex16_log.txt
	valgrind ./ex17 --log-file=ex17_log.txt