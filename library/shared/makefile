all: libfibo.so.1.0.1 fib fib-rpath fib-rpath-link

fibonacci.o: fibonacci.c
	gcc -Wall -Werror -fPIC -c $^

libfibo.so.1.0.1: fibonacci.o
	gcc -shared -Wl,-soname,libfibo.so.1 -o $@ $^
	ln -s $@ libfibo.so.1
	ln -s $@ libfibo.so

fib: main.c
	@echo
	@echo Build fib
	gcc -L. -lfibo $^ -o $@

fib-rpath: main.c
	@echo
	@echo Build fib with "-rpath"
	gcc -Wl,-rpath,$(shell pwd) -L. -lfibo $^ -o $@

fib-rpath-link: main.c
	@echo
	@echo Build fib with "-rpath-link"
	gcc -Wl,-rpath-link,$(shell pwd) -L. -lfibo $^ -o $@

clean:
	rm -f *.o *.so* fib fib-rpath fib-rpath-link