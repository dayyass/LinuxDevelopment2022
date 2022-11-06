GENERATES = move remove.so in.file out.file check-in.file
CFLAGS += -O0 -g
SO_FLAGS += -shared -fPIC

all: move

move: move.c
        cc $(CFLAGS) $^ -o $@

remove.so: remove.c
        cc $(SO_FLAGS) $^ -o  $@ -ldl

test: move remove.so
        ./tests.sh

clean:
        rm -f $(GENERATES)
