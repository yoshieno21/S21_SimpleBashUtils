#!/bin/bash
echo "-e flag"
diff  <(grep -e int s21_grep.c) <(./s21_grep -e int s21_grep.c) -s
echo "------------"

echo "-i flag"
diff  <(grep -i iNt s21_grep.c) <(./s21_grep -i iNt s21_grep.c) -s
echo "------------"

echo "-v flag"
diff  <(grep -v int s21_grep.c) <(./s21_grep -v int s21_grep.c) -s
echo "------------"

echo "-c flag"
diff  <(grep -c int s21_grep.c) <(./s21_grep -c int s21_grep.c) -s
echo "------------"

echo "-l flag"
diff  <(grep -l int s21_grep.c s21_grep.h) <(./s21_grep -l int s21_grep.c s21_grep.h) -s
echo "------------"

echo "-n flag"
diff  <(grep -n int s21_grep.c) <(./s21_grep -n int s21_grep.c) -s
echo "------------"

echo "-h flag"
diff  <(grep -h int s21_grep.c s21_grep.h) <(./s21_grep -h int s21_grep.c s21_grep.h) -s
echo "------------"

echo "-s flag with invalid file"
diff  <(grep -s int invalid.txt) <(./s21_grep -s int invalid.txt) -s
echo "------------"

echo "-f flag"
diff  <(grep -f pattern.txt s21_grep.c) <(./s21_grep -f pattern.txt s21_grep.c) -s
echo "------------"

echo "-o flag"
diff  <(grep -o return s21_grep.c) <(./s21_grep -o return s21_grep.c) -s
echo "------------"



