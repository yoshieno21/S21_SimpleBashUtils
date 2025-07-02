#include "s21_cat.h"

int main(int argc, char *argv[]) {
  struct Flags ActiveFlags = {0, 0, 0, 0, 0, 0, 0};
  int optind;
  optind = FlagsReading(argc, argv, &ActiveFlags);
  FileReading(argc, argv, optind, ActiveFlags);
}

int FlagsReading(int argc, char *argv[], struct Flags *ActiveFlags) {
  int flag;
  const char *short_options = "beEnstTv";
  const struct option long_options[] = {{"number-nonblank", 0, 0, 'b'},
                                        {"number", 0, 0, 'n'},
                                        {"squeeze-blank", 0, 0, 's'},
                                        {NULL, 0, NULL, 0}};
  while ((flag = getopt_long(argc, argv, short_options, long_options, NULL)) !=
         -1) {
    switch (flag) {
      case 'b':
        ActiveFlags->b = 1;
        break;
      case 'E':
        ActiveFlags->e = 1;
        break;
      case 'e':
        ActiveFlags->e = 1;
        ActiveFlags->v = 1;
        break;
      case 'n':
        ActiveFlags->n = 1;
        break;
      case 's':
        ActiveFlags->s = 1;
        break;
      case 'T':
        ActiveFlags->t = 1;
        break;
      case 't':
        ActiveFlags->t = 1;
        ActiveFlags->v = 1;
        break;
      case 'v':
        ActiveFlags->v = 1;
        break;
      case '?':
        ActiveFlags->er = 1;
        break;
    }
  };
  if (ActiveFlags->b == 1) ActiveFlags->n = 0;
  return optind;
}

int FileReading(int argc, char *argv[], int optind, struct Flags ActiveFlags) {
  FILE *fp;
  int fullStringsCount = 1, emptyStrings = 0;
  if (ActiveFlags.er)
    printf("usage: ./s21_cat [-belnstuv] [file ...]");
  else {
    while (optind < argc) {
      char *filename = argv[optind];
      char symbol, prevSymbol = '\n';
      fp = fopen(filename, "r");
      if (fp == NULL) {
        printf("ERROR:");
        optind = argc;
      } else {
        do {
          symbol = fgetc(fp);
          if (symbol != EOF) {
            if (prevSymbol == '\n' && symbol == '\n' && ActiveFlags.s == 1) {
              emptyStrings++;
              if (emptyStrings > 1) {
                continue;
              }
            } else {
              emptyStrings = 0;
            }

            if (prevSymbol == '\n' && ((symbol != '\n' && ActiveFlags.b == 1) ||
                                       ActiveFlags.n == 1)) {
              printf("%6d\t", fullStringsCount);
              fullStringsCount += 1;
            }
            if (symbol == '\n' && ActiveFlags.e) {
              if (ActiveFlags.b && prevSymbol == '\n') printf("\t");
              printf("$");
            }

            if (symbol == '\t' && ActiveFlags.t == 1) {
              symbol = 'I';
              printf("^");
            }
            if (((symbol >= 0 && symbol < 9) || (symbol > 10 && symbol < 32) ||
                 symbol == 127) &&
                ActiveFlags.v == 1) {
              printf("^");
              if (symbol == 127)
                symbol = 63;
              else
                symbol += 64;
            }
            printf("%c", symbol);
            prevSymbol = symbol;
          }

        } while (symbol != EOF);
        fclose(fp);
        optind++;
      }
    }
  }
  return 0;
}