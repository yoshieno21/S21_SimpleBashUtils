#!/bin/bash

echo "cat without flags"
diff <(cat s21_cat.c) <(./s21_cat s21_cat.c) -s
echo "------------"

echo "-e flag"
diff <(cat -e s21_cat.c) <(./s21_cat -e s21_cat.c) -s
echo "------------"

echo "-n flag"
diff <(cat -n s21_cat.c) <(./s21_cat -n s21_cat.c) -s
echo "------------"

echo "--number flag"
diff <(cat -n s21_cat.c) <(./s21_cat --number s21_cat.c) -s
echo "------------"

echo "-s flag"
diff <(cat -s s21_cat.c) <(./s21_cat -s s21_cat.c) -s
echo "------------"

echo "--squeeze-blank"
diff <(cat -s s21_cat.c) <(./s21_cat --squeeze-blank s21_cat.c) -s
echo "------------"

echo "-t flag"
diff <(cat -t s21_cat.c) <(./s21_cat -t s21_cat.c) -s
echo "------------"

echo "-v flag"
diff <(cat -v s21_cat.c) <(./s21_cat -v s21_cat.c) -s
echo "------------"

echo "cat with two files"
diff <(cat s21_cat.c s21_cat.h) <(./s21_cat s21_cat.c s21_cat.h) -s
echo "------------"