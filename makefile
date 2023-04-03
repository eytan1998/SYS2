.PHONY: all clean

all: basic cmp copy encode decode libcodecA.so libcodecB.so

encode: encode.o
	gcc -o encode encode.o

encode.o: encode.c
	gcc -c encode.c

decode: decode.o
	gcc -o decode decode.o

decode.o: decode.c
	gcc -c decode.c

libcodecA.so : codecA.o
	gcc -shared -o $@ $^

codecA.o: codecA.c
	gcc -fPIC -c codecA.c

libcodecB.so : codecB.o
	gcc -shared -o $@ $^

codecB.o: codecB.c
	gcc -fPIC -c codecB.c

copy: copy.o
	gcc -o copy copy.o

copy.o: copy.c
	gcc -c copy.c

cmp: cmp.o
	gcc -o cmp cmp.o

cmp.o: cmp.c
	gcc -c cmp.c

basic: basic_shell.o
	gcc -o basic basic_shell.o

basic_shell.o: basic_shell.c
	gcc -o basic_shell.o -c basic_shell.c


clean:
	rm -f *.o *.so basic cmp copy decode encode