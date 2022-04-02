cc = gcc
target = fish

objects = main.o

$(target) : $(objects)
		$(cc) -g -o $(target) $(objects) -lncurses

%.o : %.c
		$(cc) -g -c -o $@ $<

.PHONY : clean
clean :
		rm $(target) $(objects)
