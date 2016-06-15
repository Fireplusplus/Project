main:ping.o main.o
	gcc -o main ping.o main.o -lm
ping.o:ping.c
	gcc -c ping.c -o ping.o -lm
main.o:main.c
	gcc -c main.c -o main.o -lm
.PHONY:clean
clean:
	rm -rf ping.o main.o main
