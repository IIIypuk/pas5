CC=tcc

.PHONY: all clean

all:
	$(CC) ./src/pas5.c -o pas5 -lsqlite3

clean:
	rm -f pas5
