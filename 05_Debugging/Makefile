GENERATES = range output-gdb.txt
CFLAGS += -O0 -g

all: range

range: range.c
	cc $(CFLAGS) $^ -o $@

run_%: range
	rm -f output-gdb.txt
	gdb -x gdb-script$*.txt --args $< > /dev/null
	cat output-gdb.txt | grep @@@ | cmp answer$*.txt
	rm -f output-gdb.txt

test: run_1 run_2

clean:
	rm -f $(GENERATES)

