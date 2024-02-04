#include "cat_realization.h"

#include <stdlib.h>
#include <string.h>

#include "../common/check_files.h"

void cat(char **file_names, int count, char *option) {
  check_files(file_names, count, "cat");
  for (int i = 0; i < count; i++) {
    FILE *fp = fopen(file_names[i], "r");
    if (fp) {
      if (option == NULL)
        cat_without_flag(fp);
      else if (!strcmp(option, "-b") || !strcmp(option, "--number-nonblank"))
        cat_b(fp);
      else if (!strcmp(option, "-e") || !strcmp(option, "-E"))
        cat_e(option, fp);
      else if (!strcmp(option, "-n") || !strcmp(option, "--number"))
        cat_n(fp);
      else if (!strcmp(option, "-s") || !strcmp(option, "--squeeze-blank"))
        cat_s(fp);
      else if (!strcmp(option, "-t") || !strcmp(option, "-T"))
        cat_t(option, fp);
      fclose(fp);
    }
  }
}
void cat_b(FILE *fp) {
  int num = 1;
  char *buf = NULL;
  size_t len = 0;
  ssize_t read;
  while ((read = getline(&buf, &len, fp)) != -1) {
    if (strlen(buf) != 0 && strcmp(buf, "\n")) {
      printf("%6d\t%s", num, buf);
      num++;
    } else
      printf("%s", buf);
  }

  free(buf);
}
void cat_e(char *option, FILE *fp) {
  char *buf = NULL;
  size_t len = 0;
  ssize_t read;
  while ((read = getline(&buf, &len, fp)) != -1) {
    for (size_t i = 0; i < strlen(buf); i++) {
      if (buf[i] == '\r' && !strcmp(option, "-e")) {
        printf("^M");
        continue;
      }
      if (buf[i] == '\n') printf("$");

      printf("%c", buf[i]);
    }
  }

  free(buf);
}
void cat_n(FILE *fp) {
  int num = 1;
  char *buf = NULL;
  size_t len = 0;
  ssize_t read;
  while ((read = getline(&buf, &len, fp)) != -1) {
    printf("%6d\t%s", num, buf);
    num++;
  }

  free(buf);
}
void cat_s(FILE *fp) {
  char *buf = NULL;
  size_t len = 0;
  ssize_t read;
  char *prev_buf = NULL;
  while (1) {
    if (buf != NULL) {
      free(prev_buf);
      prev_buf = strdup(buf);
    }

    if ((read = getline(&buf, &len, fp)) == -1) break;

    if (prev_buf && buf && (!strcmp(prev_buf, "\n") && !strcmp(buf, "\n")))
      continue;
    printf("%s", buf);
  }

  free(buf);
  free(prev_buf);
}
void cat_t(char *option, FILE *fp) {
  char *buf = NULL;
  size_t len = 0;
  ssize_t read;
  while ((read = getline(&buf, &len, fp)) != -1) {
    for (size_t i = 0; i < strlen(buf); i++) {
      if (buf[i] == '\r' && !strcmp(option, "-t")) {
        printf("^M");
        continue;
      }
      if (buf[i] == '\t') {
        printf("^I");
        continue;
      }
      printf("%c", buf[i]);
    }
  }

  free(buf);
}
void cat_without_flag(FILE *fp) {
  char *buf = NULL;
  size_t len = 0;
  ssize_t read;
  while ((read = getline(&buf, &len, fp)) != -1) printf("%s", buf);

  free(buf);
}