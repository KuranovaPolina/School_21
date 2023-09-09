#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX 1024

void grep(int argc, char **argv);

int main(int argc, char **argv) {
  grep(argc, argv);

  return 0;
}

void grep(int argc, char **argv) {
  FILE *fp;
  char buffer[MAX];
  char *pattern = NULL;
  int fileInd, opt, z, fileCount;
  int eFlag = 0, iFlag = 0, vFlag = 0, cFlag = 0, lFlag = 0, nFlag = 0;
  int hFlag = 0, sFlag = 0, fFlag = 0, oFlag = 0;
  int continueStatus = 1;
  int count = 0, lineCount = 0;
  regex_t reg;

  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
      case 'e':
        eFlag++;
        if (pattern == NULL) {
          pattern = optarg;
        } else {
          pattern = strcat(pattern, "|");
          pattern = strcat(pattern, optarg);
        }
        break;
      case 'i':
        iFlag++;
        break;
      case 'v':
        vFlag++;
        break;
      case 'c':
        cFlag++;
        break;
      case 'l':
        lFlag++;
        break;
      case 'n':
        nFlag++;
        break;
      case 'h':
        hFlag++;
        break;
      case 's':
        sFlag++;
        break;
      case 'f':
        fFlag++;
        fp = fopen(optarg, "rb");
        if (fp == NULL) {
          printf("grep: %s: No such file or directory\n", optarg);
        } else {
          while (fgets(buffer, MAX, fp)) {
            if (pattern == NULL) {
              pattern = buffer;
            }
          }
          fclose(fp);
        }

        break;
      case 'o':
        oFlag++;
        break;
    }
  }

  if (optind >= argc) {
    continueStatus = 0;
    printf("No parameters\n");
  }

  if (continueStatus) {
    if (pattern == NULL && optind < argc) {
      pattern = argv[optind];
      fileInd = optind + 1;
    } else {
      fileInd = optind;
    }

    if (iFlag) {
      z = regcomp(&reg, pattern, REG_ICASE);
    } else {
      z = regcomp(&reg, pattern, REG_EXTENDED);
    }

    if (z != 0) {
      continueStatus = 0;
      printf("grep: Invalid regular expression\n");
    }

    fileCount = argc - fileInd;
    while (fileInd < argc && continueStatus) {
      fp = fopen(argv[fileInd], "rb");
      if (fp == NULL) {
        if (!sFlag) {
          printf("grep: %s: No such file or directory\n", argv[fileInd]);
        }
      } else {
        while (fgets(buffer, MAX, fp)) {
          int length = strlen(buffer);
          regmatch_t pmatch[10];
          const size_t nmatch = 10;
          int status = regexec(&reg, buffer, nmatch, pmatch, 0);

          lineCount++;

          if ((status == 0 && !vFlag) || (status != 0 && vFlag)) {
            count++;
            if (!lFlag && !cFlag) {
              char lastl;
              if (!hFlag && fileCount > 1) {
                printf("%s:", argv[fileInd]);
              }
              if (nFlag) {
                printf("%d:", lineCount);
              }
              for (int i = 0; i < length; i++) {
                printf("%c", buffer[i]);
                lastl = buffer[i];
              }
              if (lastl != '\n') {
                printf("\n");
              }
            }
          }
        }

        fclose(fp);

        if (lFlag && count) {
          printf("%s\n", argv[fileInd]);
        }

        if (cFlag && !lFlag) {
          if (!hFlag && fileCount > 1) {
            printf("%s:", argv[fileInd]);
          }
          printf("%d\n", count);
        }
      }

      count = 0;
      lineCount = 0;

      fileInd++;
    }

    regfree(&reg);
  }
}
