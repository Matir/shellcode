ALL := linux-x86 linux-x64

all: $(ALL)

linux-x86: linux.c
	gcc -m32 -o linux-x86 linux.c

linux-x64: linux.c
	gcc -m64 -o linux-x64 linux.c

clean:
	rm $(ALL)
