all: hw0401.o hw0403.o myprintf.c 
	gcc hw0401.o -o hw0401 -lm
	gcc myprintf.c hw0403.o -o hw0403 -lm

hw0401: hw0401.c
	gcc -c hw0401.c -o hw0401.o -lm
	gcc -shared hw0401.o -o libhw0401.so

hw0403: hw0403.c
	gcc -c hw0403.c -o hw0403.o -lm
	gcc -shared hw0403.o -o libhw0403.so


