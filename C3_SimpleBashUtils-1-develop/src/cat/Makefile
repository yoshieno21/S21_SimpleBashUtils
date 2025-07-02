all: s21_cat

build: s21_cat

s21_cat: 
	gcc -Wall -Werror -Wextra -std=c11 s21_cat.c s21_cat.h -o s21_cat

test: s21_cat
	chmod 777 test.sh
	./test.sh

rebuild: clean all

clean:
	rm s21_cat