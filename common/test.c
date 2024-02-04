#include "test.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../cat/cat_realization.h"
#include "../grep/grep_realization.h"

void compare_files(char *bash_output_filename, char *my_output_filename) {
  FILE *fp_bash = fopen(bash_output_filename, "r");
  FILE *fp_my = fopen(my_output_filename, "r");

  char *buf_bash = NULL, *buf_my = NULL;
  size_t len_bash = 0, len_my = 0;
  ssize_t read_bash, read_my;

  while ((read_bash = getline(&buf_bash, &len_bash, fp_bash)) != -1 &&
         (read_my = getline(&buf_my, &len_my, fp_my)) != -1)
    assert(!strcmp(buf_my, buf_bash));

  free(buf_bash);
  free(buf_my);

  fclose(fp_bash);
  fclose(fp_my);
}
void make_bash_command_output(char *cat_or_grep, char **argv, int argc,
                              char *bash_output_filename) {
  char command[1000] = {'\0'};
  strcat(command, cat_or_grep);
  strcat(command, " ");
  for (int i = 1; i < argc; i++) {
    strcat(command, argv[i]);
    strcat(command, " ");
  }
  strcat(command, "> ");
  strcat(command, bash_output_filename);
  strcat(command, " 2>&1");

  system(command);
}
void test(char *cat_or_grep, char **argv, int argc, bool is_correct_option,
          bool is_correct_template, char **file_names, int count, char *option,
          char *template) {
  char *bash_output_filename = "bash_output.txt";
  char *my_output_filename = "my_output.txt";

  make_bash_command_output(cat_or_grep, argv, argc, bash_output_filename);

  FILE *fp = fopen(my_output_filename, "w");
  freopen(my_output_filename, "w", stdout);
  if (is_correct_option) {
    if (!strcmp(cat_or_grep, "cat"))
      cat(file_names, count, option);
    else if (is_correct_template) {
      regex_t regex;
      make_template(template, &regex);
      grep(file_names, count, option, regex, template);
      regfree(&regex);
    }
  } else if (!strcmp(cat_or_grep, "cat"))
    printf(
        "cat: invalid option -- '%c'\nTry 'cat --help' for more information.\n",
        argv[1][1]);
  else if (!strcmp(cat_or_grep, "grep"))
    printf(
        "grep: invalid option -- '%c'\nUsage: grep [OPTION]... PATTERNS "
        "[FILE]...\nTry 'grep --help' for more information.\n",
        argv[1][1]);

  fclose(fp);
  freopen("/dev/tty", "w", stdout);

  compare_files(bash_output_filename, my_output_filename);
}