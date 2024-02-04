#include "input_data.h"

#include <stdlib.h>
#include <string.h>

char *create_option_cat(char **input_strings) {
  if (!strcmp(input_strings[1], "-b") || !strcmp(input_strings[1], "-e") ||
      !strcmp(input_strings[1], "-n") || !strcmp(input_strings[1], "-s") ||
      !strcmp(input_strings[1], "-t") ||
      !strcmp(input_strings[1], "--number-nonblank") ||
      !strcmp(input_strings[1], "-E") ||
      !strcmp(input_strings[1], "--number") ||
      !strcmp(input_strings[1], "--squeeze-blank") ||
      !strcmp(input_strings[1], "-T")) {
    return input_strings[1];
  } else {
    char *error = "invalid option";
    return error;
  }
}
char *create_option_grep(char *option) {
  if (!strcmp(option, "-e") || !strcmp(option, "-i") || !strcmp(option, "-v") ||
      !strcmp(option, "-c") || !strcmp(option, "-l") || !strcmp(option, "-n") ||
      !strcmp(option, "-h") || !strcmp(option, "-s") || !strcmp(option, "-o") ||
      !strcmp(option, "-f")) {
    return option;
  } else {
    char *error = "invalid option";
    return error;
  }
}
char **file_names(int grep_or_cat, int *size, int elem_num,
                  char **input_strings, char *option) {
  int start_point = 3;
  if (!grep_or_cat) start_point = 2;
  if (!grep_or_cat && !option) start_point = 1;

  *size = elem_num - start_point;

  char **fl_names = (char **)malloc((elem_num - start_point) * sizeof(char *));
  for (int i = 0; i < elem_num - start_point; i++)
    fl_names[i] = (char *)malloc(20 * sizeof(char));

  for (int i = start_point; i < elem_num; i++)
    strcpy(fl_names[i - start_point], input_strings[i]);

  return fl_names;
}
void free_array(int size, char **array) {
  for (int i = 0; i < size; i++) free(array[i]);
  free(array);
}