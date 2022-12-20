all: forksA forksB soup
forksA: src/forksA.c
	gcc -o bin/forksA src/forksA.c
forksB: src/forksB.c
	gcc -o bin/forksB src/forksB.c
soup: src/soup.c
	gcc -o bin/soup src/soup.c
clean:
	rm -f bin/*