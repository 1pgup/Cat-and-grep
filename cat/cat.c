#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/input_data.h"
#include "../common/test.h"
#include "cat_realization.h"

#define OPTION_ERROR -1
#define TOO_FEW_ELEMENTS_ERROR -2

int main(int argc, char *argv[]) {
  if (argc >= 2) {
    char *option = NULL;
    if (strchr(argv[1], '-')) option = create_option_cat(argv);

    bool working_with_correct_option =
        !(option && !strcmp(option, "invalid option"));
    if (working_with_correct_option) {
      int size = 0;
      char **fl_names = file_names(0, &size, argc, argv, option);
      cat(fl_names, size, option);
      test("cat", argv, argc, working_with_correct_option, true, fl_names, size,
           option, NULL);

      free_array(size, fl_names);
    } else {
      printf(
          "cat: invalid option -- '%c'\nTry 'cat --help' for more "
          "information.\n",
          argv[1][1]);
      test("cat", argv, argc, working_with_correct_option, true, NULL, 0, NULL,
           NULL);
      return OPTION_ERROR;
    }
  } else {
    printf("cat: Too few input arguments\n");
    return TOO_FEW_ELEMENTS_ERROR;
  }
  return 0;
}
