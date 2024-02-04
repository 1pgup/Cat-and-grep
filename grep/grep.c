#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "../common/input_data.h"
#include "../common/test.h"
#include "grep_realization.h"

#define OPTION_ERROR -1
#define TEMPLATE_ERROR -2
#define TOO_FEW_ELEMENTS_ERROR -3

int main(int argc, char *argv[]) {
  if (argc >= 4) {
    char *option = create_option_grep(argv[1]);

    bool working_with_correct_option = strcmp(option, "invalid option");

    if (working_with_correct_option) {
      regex_t regex;
      char *tmplt = argv[2];
      bool working_with_correct_template = !make_template(tmplt, &regex);
      if (working_with_correct_template) {
        int size = 0;
        char **fl_names = file_names(1, &size, argc, argv, option);

        grep(fl_names, size, option, regex, tmplt);
        test("grep", argv, argc, working_with_correct_option,
             working_with_correct_template, fl_names, size, option, tmplt);
        regfree(&regex);
        free_array(size, fl_names);
      } else {
        printf("grep: invalid template %s\n", tmplt);
        regfree(&regex);
        return TEMPLATE_ERROR;
      }
    } else {
      printf(
          "grep: invalid option -- '%c'\nUsage: grep [OPTION]... PATTERNS "
          "[FILE]...\nTry 'grep --help' for more "
          "information.\n",
          argv[1][1]);
      test("grep", argv, argc, working_with_correct_option, false, NULL, 0,
           NULL, NULL);
      return OPTION_ERROR;
    }
  } else {
    printf("grep: Too few input arguments\n");
    return TOO_FEW_ELEMENTS_ERROR;
  }
  return 0;
}
