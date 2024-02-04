#ifndef INPUT_DATA_H
#define INPUT_DATA_H

#include <stdio.h>

char *create_option_cat(char **input_strings);
char *create_option_grep(char *option);
char **file_names(int grep_or_cat, int *size, int elem_num,
                  char **input_strings, char *option);

void free_array(int size, char **array);

#endif /* INPUT_DATA_H */
