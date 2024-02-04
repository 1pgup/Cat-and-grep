#include "check_files.h"

void check_files(char **file_names, int count, char *cat_or_grep) {
  for (int i = 0; i < count; i++) {
    FILE *fp = fopen(file_names[i], "r");
    if (!fp)
      printf("%s: %s: No such file or directory\n", cat_or_grep, file_names[i]);
    else
      fclose(fp);
  }
}