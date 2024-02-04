#ifndef TEST_H
#define TEST_H

#include <regex.h>
#include <stdbool.h>

void compare_files(char *bash_output_filename, char *my_output_filename);
void make_bash_command_output(char *cat_or_grep, char **argv, int argc,
                              char *bash_output_filename);
void test(char *cat_or_grep, char **argv, int argc, bool is_correct_option,
          bool is_correct_template, char **file_names, int count, char *option,
          char *template);

#endif /* TEST_H */
