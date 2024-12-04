OBJ=$(patsubst %.c,%.o,$(wildcard *.c))
mp3.out : $(OBJ)
	gcc -o $@ $^
clean :
	rm *.o *.out

