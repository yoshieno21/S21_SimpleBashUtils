all: s21_grep

build: s21_grep

s21_grep: 
	gcc -Wall -Werror -Wextra -std=c11 s21_grep.c s21_grep.h -o s21_grep

test: s21_grep
	chmod 777 test.sh
	./test.sh

rebuild: clean all

clean:
	rm s21_grep