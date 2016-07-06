CC=g++
SRC=src/main.cc

OUT=prpa

CFLAGS = `pkg-config --cflags opencv`
LIBS = `pkg-config --libs opencv`

all:
	$(CC) $(CFLAGS) $(LIBS) -o $(OUT) $(SRC)
