#ifndef S21_CAT_H
#define S21_CAT_H

#include <getopt.h>
#include <stdio.h>
struct Flags {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
  int er;
};
int FlagsReading(int argc, char *argv[], struct Flags *ActiveFlags);
int FileReading(int argc, char *argv[], int optind, struct Flags ActiveFlags);
#endif