FLAGS = -lncurses -I$(IDIR)
SRCS = ./src/*.c
IDIR = ./include/

all: rogue run clean

rogue: $(IDIR)*.h
	gcc -o $@ $(SRCS) $(FLAGS)

run:
	./rogue

clean:
	rm rogue
