GENERATES = prog prog-a prog-so README liboutput_static.a liboutput.so
TRASH = *.o *~ o.* *.result
CFLAGS += -fPIC

all:    README prog prog-a prog-so

prog:   const.o fun.o prog.o

prog-a:    prog.o liboutput_static.a
	cc -L. $< -loutput_static -o $@

prog-so:    prog.o liboutput.so
	cc -L. $< -loutput -o $@

test:    all
	./prog 2> prog_0.result 1>&2
	./prog-a 2> prog-a_0.result 1>&2
	LD_LIBRARY_PATH="." ./prog-so 2> prog-so_0.result 1>&2
	-cmp prog_0.result prog-a_0.result
	-cmp prog_0.result prog-so_0.result
	
	./prog abc 2> prog_1.result 1>&2
	./prog-a abc 2> prog-a_1.result 1>&2
	LD_LIBRARY_PATH="." ./prog-so abc 2> prog-so_1.result 1>&2
	-cmp prog_1.result prog-a_1.result
	-cmp prog_1.result prog-so_1.result
	
	./prog abc 123 qqq 2> prog_2.result 1>&2
	./prog-a abc 123 qqq 2> prog-a_2.result 1>&2
	LD_LIBRARY_PATH="." ./prog-so abc 123 qqq 2> prog-so_2.result 1>&2
	-cmp prog_2.result prog-a_2.result
	-cmp prog_2.result prog-so_2.result

README: prog
	./$< 2> $@

fun.o:  outlib.h

liboutput_static.a:   fun.o const.o
	ar -rcs $@ $^

liboutput.so:    fun.o const.o
	cc -shared $^ -o $@

clean:
	rm -f $(TRASH)

distclean:      clean
	rm -rf $(GENERATES)

