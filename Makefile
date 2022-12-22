all: forksA forksB soupA soupB
forksA: src/forksA.c
	gcc -o bin/forksA src/forksA.c -pthread
forksB: src/forksB.c
	gcc -o bin/forksB src/forksB.c -pthread
soupA: src/soupA.c
	gcc -o bin/soupA src/soupA.c -pthread
soupB: src/soupB.c
	gcc -o bin/soupB src/soupB.c -pthread
clean:
	rm -f bin/*