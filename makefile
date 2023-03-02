FLAGS = -Wall -Werror

myPs:
	gcc myPs.c -c $(FLAGS)

main: myPs
	gcc myPs.o main.c -o main.out $(FLAGS)

clean:
	rm -rf *.o
