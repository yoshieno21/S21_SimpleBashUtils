#ifndef S21_GREP_H
#define S21_GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>

struct Flags {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
};

int FlagsReading(int argc, char *argv[], struct Flags *ActiveFlags);
int FindPattern(int argc, char *argv[], int optind, struct Flags ActiveFlags);
#endif