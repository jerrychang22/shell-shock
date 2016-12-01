all:
	gcc main.c parse.c -o main

run:
	./main

clean:
	rm *.o *~
