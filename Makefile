CC=tcc

all:
	$(CC) ./src/pas5.c -o pas5 -lsqlite3

clean:
	rm pas5
