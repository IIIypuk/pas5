CC=tcc

.PHONY: all clean

ifeq ($(OS),Windows_NT)
all: sqlite3.def
	$(CC) sqlite3.def ./src/deps/xgetopt/xgetopt.c ./src/pas5.c -o pas5.exe -I.
else
all:
	$(CC) ./src/pas5.c -o pas5 -lsqlite3
endif

sqlite3.def:
	tiny_impdef sqlite3.dll

ifeq ($(OS),Windows_NT)
clean:
	del /f pas5.exe
	del /f sqlite3.def
else
clean:
	rm -f pas5
endif
