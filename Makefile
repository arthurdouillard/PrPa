CC=g++
SRC=src/main.cc src/options/options.cc

OUT=prpa

CFLAGS = `pkg-config --cflags opencv`
LIBS = `pkg-config --libs opencv`
OPENCV=$(CFLAGS) $(LIBS)

BPO=boost_program_options

all:
	$(CC) $(OPENCV) -l$(BPO) -o $(OUT) $(SRC)

clean:
	rm $(OUT)
