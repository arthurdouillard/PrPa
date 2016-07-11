CC=g++
SRC=src/main.cc                  \
    src/options/options.cc       \
    src/filter/grayscale.cc      \
    src/filter/writer.cc         \
    src/filter/modelfilter.cc    \
    src/filter/sepia.cc          \
    src/filter/binary.cc         \
    src/filter/sharpen.cc        \
    src/filter/gaussian.cc       \
    src/filter/verticalflip.cc   \
	src/filter/image_overlay.cc  \
    src/filter/false_writer.cc

OUT=prpa

# --  Library
# OpenCv
CFLAGS = `pkg-config --cflags opencv`
LIBS = `pkg-config --libs opencv`
OPENCV=$(CFLAGS) $(LIBS)
# Boost opt
BPO=-lboost_program_options
# TBB
TBB=-lrt -ltbb

all:
	$(CC) $(OPENCV) $(BPO) $(TBB) -O3 -o $(OUT) $(SRC)

debug:
	$(CC) $(OPENCV) $(BPO) $(TBB) -g3 -O0 -o $(OUT) $(SRC)
clean:
	rm -f $(OUT)
