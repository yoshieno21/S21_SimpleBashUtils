#include "s21_grep.h"

int main(int argc, char *argv[]) {
  struct Flags ActiveFlags = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int optind;
  optind = FlagsReading(argc, argv, &ActiveFlags);
  FindPattern(argc, argv, optind, ActiveFlags);
  return 0;
}

int FlagsReading(int argc, char *argv[], struct Flags *ActiveFlags) {
  int flag;
  while ((flag = getopt(argc, argv, "eivclnhsfo")) != -1) {
    switch (flag) {
      case 'i':
        ActiveFlags->i = 1;
        ActiveFlags->e = 0;
        break;
      case 'c':
        ActiveFlags->c = 1;
        ActiveFlags->e = 0;
        break;
      case 'e':
        ActiveFlags->e = 1;
        break;
      case 'n':
        ActiveFlags->n = 1;
        ActiveFlags->e = 0;
        break;
      case 'l':
        ActiveFlags->l = 1;
        ActiveFlags->e = 0;
        break;
      case 'v':
        ActiveFlags->v = 1;
        ActiveFlags->e = 0;
        break;
      case 'h':
        ActiveFlags->h = 1;
        break;
      case 'f':
        ActiveFlags->f = 1;
        break;
      case 's':
        ActiveFlags->s = 1;
        break;
      case 'o':
        ActiveFlags->o = 1;
        ActiveFlags->e = 0;
        break;
    }
  };
  return optind;
}

int FindPattern(int argc, char *argv[], int optind, struct Flags ActiveFlags) {
  char *file, *template;
  int matchedStringCounter = 0, matchedFile = 0, fileStringCounter = 0;
  FILE *fp;
  regex_t re;
  char buffer[4096];
  char fpattern[4096];
  int printName = 0;
  int patternFail = 0;

  if (ActiveFlags.f == 1) {
    fp = fopen(argv[optind++], "r");
    if (fp == NULL) {
      optind = argc;
      patternFail = 1;
      if (ActiveFlags.s == 0)
        printf("ERROR: PATTERN FILE NOT FOUND OR NOT EXIST");
    } else {
      fgets(fpattern, 4096, fp);
      regcomp(&re, fpattern, 0);
      fclose(fp);
    }
  } else {
    template = argv[optind++];

    if (ActiveFlags.i == 1)
      regcomp(&re, template, REG_ICASE);
    else
      regcomp(&re, template, 0);
  }
  if (argc - optind > 1 && ActiveFlags.h == 0) printName = 1;
  while (optind < argc) {
    file = argv[optind++];
    fp = fopen(file, "r");
    if (fp == NULL) {
      if (ActiveFlags.s == 0) {
        printf("ERROR:FILE NOT FOUND OR NOT EXIST\n");
      }
      optind = argc;
    } else {
      while (fgets(buffer, 4096, fp) != NULL) {
        fileStringCounter++;
        if (ActiveFlags.n == 1 && regexec(&re, buffer, 0, NULL, 0) == 0) {
          if (printName) printf("%s:", file);
          printf("%d:", fileStringCounter);
          fputs(buffer, stdout);
        }
        if (ActiveFlags.e == 1 && regexec(&re, buffer, 0, NULL, 0) == 0) {
          if (printName) printf("%s:", file);
          fputs(buffer, stdout);
        }
        if (ActiveFlags.v == 1 && regexec(&re, buffer, 0, NULL, 0) != 0) {
          if (printName) printf("%s:", file);
          fputs(buffer, stdout);
        }
        if (ActiveFlags.i == 1 && ActiveFlags.c == 0 && ActiveFlags.l == 0 &&
            ActiveFlags.n != 1 && ActiveFlags.v != 1) {
          if (regexec(&re, buffer, 0, NULL, 0) == 0) {
            if (printName) printf("%s:", file);
            fputs(buffer, stdout);
          }
        }
        if (ActiveFlags.c == 1 && regexec(&re, buffer, 0, NULL, 0) == 0)
          matchedStringCounter++;
        if (ActiveFlags.l == 1 && regexec(&re, buffer, 0, NULL, 0) == 0)
          matchedFile = 1;
        if (ActiveFlags.o == 1 && regexec(&re, buffer, 0, NULL, 0) == 0) {
          printf("%s\n", template);
        }
      }
      if (ActiveFlags.c == 1) printf("%d\n", matchedStringCounter);
      if (ActiveFlags.l == 1 && matchedFile == 1) {
        matchedFile = 0;
        printf("%s\n", file);
      }
      fclose(fp);
    }
  }
  if (patternFail == 0) regfree(&re);
  return 0;
}
