#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX 1024

void cat(int argc, char **argv);
void myPrintCat(char buffer[MAX], int flags[6]);

int main(int argc, char **argv) {
  cat(argc, argv);

  return 0;
}

void cat(int argc, char **argv) {
  FILE *fp;
  char buffer[MAX];
  int fileInd, opt;
  int bFlag = 0, eFlag = 0, nFlag = 0, sFlag = 0, tFlag = 0, vFlag = 0;
  int continueStatus = 1;

  const struct option long_opts[] = {{"number-nonblank", 0, NULL, 'b'},
                                     {"number", 0, NULL, 'n'},
                                     {"squeeze-blank", 0, NULL, 's'}};
  const char *const short_opts = "beEvnstT";

  while ((opt = (getopt_long(argc, argv, short_opts, long_opts, NULL))) != -1) {
    switch (opt) {
      case 'b':
        bFlag++;
        break;
      case 'e':
        vFlag++;
        eFlag++;
        break;
      case 'E':
        eFlag++;
        break;
      case 'n':
        nFlag++;
        break;
      case 's':
        sFlag++;
        break;
      case 't':
        vFlag++;
        tFlag++;
        break;
      case 'T':
        tFlag++;
        break;
      case 'v':
        vFlag++;
        break;
      default:
        continueStatus = 0;
    }
  }

  if (continueStatus) {
    fileInd = optind;

    if (fileInd == argc) {
      while (1) {
        while (fgets(buffer, MAX, stdin)) {
          int flags[] = {bFlag, eFlag, nFlag, sFlag, tFlag, vFlag};
          myPrintCat(buffer, flags);
        }
      }
    } else {
      while (fileInd < argc) {
        fp = fopen(argv[fileInd], "rb");
        if (fp == NULL) {
          printf("cat: %s: No such file or directory\n", argv[fileInd]);
        } else {
          while (fgets(buffer, MAX, fp)) {
            int flags[] = {bFlag, eFlag, nFlag, sFlag, tFlag, vFlag};
            myPrintCat(buffer, flags);
          }
          fclose(fp);
        }

        fileInd++;
      }
    }
  }
}

void myPrintCat(char buffer[MAX], int flags[6]) {
  static int line = 1, end = 1;
  int length = strlen(buffer);
  int continueStatus = 1, currentBlankStatus;
  int bFlag = flags[0], eFlag = flags[1], nFlag = flags[2], sFlag = flags[3],
      tFlag = flags[4], vFlag = flags[5];
  static int lastBlankStatus = 0;

  if (sFlag) {
    currentBlankStatus = (length > 1) ? 0 : 1;
    if (currentBlankStatus && lastBlankStatus) {
      continueStatus = 0;
    }
    lastBlankStatus = currentBlankStatus;
  }

  if (continueStatus) {
    if (bFlag && end) {
      if (length > 1) {
        printf("%6d\t", line++);
      }
    } else if (nFlag && end) {
      printf("%6d\t", line++);
    }

    end = 1;

    for (int i = 0; i < length; i++) {
      char letter = buffer[i];
      if (tFlag && letter == '\t') {
        printf("^I");
      } else if (eFlag && letter == '\n') {
        printf("$\n");
      } else if (vFlag && ((int)letter == 0)) {
        printf("^@");
      } else if (vFlag && (((int)letter > 0 && (int)letter <= 8) ||
                           ((int)letter >= 11 && (int)letter <= 26))) {
        printf("^%c", (char)((int)letter + 'A' - 1));
      } else if (vFlag && (int)letter == 27) {
        printf("^[");
      } else if (vFlag && (int)letter == 28) {
        printf("^\\");
      } else if (vFlag && (int)letter == 29) {
        printf("^]");
      } else if (vFlag && (int)letter == 30) {
        printf("^^");
      } else if (vFlag && (int)letter == 31) {
        printf("^_");
      } else if (vFlag && (int)letter == 127) {
        printf("^?");
      } else {
        printf("%c", letter);
      }

      if (i == (length - 1) && letter != '\n') {
        end = 0;
      }
    }
  }
}
