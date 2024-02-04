#include "grep_realization.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "../common/check_files.h"
#include "../common/input_data.h"

int make_template(char *input_template, regex_t *regex) {
  int status = regcomp(regex, input_template, 0);
  return status;
}
void grep(char **file_names, int count, char *option, regex_t regex,
          char *template) {
  FILE *fp_f = NULL;
  if (!strcmp(option, "-f")) {
    fp_f = fopen(template, "r");

    if (!fp_f) {
      printf("grep: %s: No such file or directory\n", template);
      return;
    }
  }
  if (strcmp(option, "-s")) check_files(file_names, count, "grep");
  for (int i = 0; i < count; i++) {
    FILE *fp = fopen(file_names[i], "r");

    if (fp) {
      if (!strcmp(option, "-e"))
        grep_e(count, file_names[i], fp, regex);
      else if (!strcmp(option, "-i"))
        grep_i(count, file_names[i], fp, template);
      else if (!strcmp(option, "-v"))
        grep_v(count, file_names[i], fp, regex);
      else if (!strcmp(option, "-c"))
        grep_c(count, file_names[i], fp, regex);
      else if (!strcmp(option, "-l"))
        grep_l(file_names[i], fp, regex);
      else if (!strcmp(option, "-n"))
        grep_n(count, file_names[i], fp, regex);
      else if (!strcmp(option, "-h"))
        grep_h(fp, regex);
      else if (!strcmp(option, "-s"))
        grep_e(count, file_names[i], fp, regex);
      else if (!strcmp(option, "-f"))
        grep_f(count, file_names[i], fp, fp_f);
      else if (!strcmp(option, "-o"))
        grep_o(count, file_names[i], fp, regex);

      fclose(fp);
    }
  }
  if (fp_f) fclose(fp_f);
}
void grep_e(int count, char *file_name, FILE *fp, regex_t regex) {
  char *buf = NULL;
  size_t len = 0;
  ssize_t read;
  while ((read = getline(&buf, &len, fp)) != -1) {
    buf[strcspn(buf, "\n")] = '\0';
    int status = regexec(&regex, buf, 0, NULL, 0);
    if (!status) {
      if (count > 1)
        printf("%s:%s\n", file_name, buf);
      else
        printf("%s\n", buf);
    }
  }

  free(buf);
}
void grep_i(int count, char *file_name, FILE *fp, char *template) {
  for (size_t i = 0; i < strlen(template); i++)
    template[i] = tolower(template[i]);

  regex_t regex;
  make_template(template, &regex);

  char *buf = NULL;
  size_t len = 0;
  ssize_t read;
  while ((read = getline(&buf, &len, fp)) != -1) {
    buf[strcspn(buf, "\n")] = '\0';
    char tmp_buf[strlen(buf) + 1];
    for (size_t i = 0; i < strlen(buf); i++) tmp_buf[i] = tolower(buf[i]);
    tmp_buf[strlen(buf)] = '\0';

    int status = regexec(&regex, tmp_buf, 0, NULL, 0);
    if (!status) {
      if (count > 1)
        printf("%s:%s\n", file_name, buf);
      else
        printf("%s\n", buf);
    }
  }
  regfree(&regex);
  free(buf);
}
void grep_v(int count, char *file_name, FILE *fp, regex_t regex) {
  char *buf = NULL;
  size_t len = 0;
  ssize_t read;
  while ((read = getline(&buf, &len, fp)) != -1) {
    buf[strcspn(buf, "\n")] = '\0';
    int status = regexec(&regex, buf, 0, NULL, 0);
    if (status) {
      if (count > 1)
        printf("%s:%s\n", file_name, buf);
      else
        printf("%s\n", buf);
    }
  }

  free(buf);
}
void grep_c(int count, char *file_name, FILE *fp, regex_t regex) {
  int result = 0;
  char *buf = NULL;
  size_t len = 0;
  ssize_t read;
  while ((read = getline(&buf, &len, fp)) != -1) {
    int status = regexec(&regex, buf, 0, NULL, 0);
    if (!status) {
      result++;
    }
  }
  if (count > 1)
    printf("%s:%d\n", file_name, result);
  else
    printf("%d\n", result);

  free(buf);
}
void grep_l(char *file_name, FILE *fp, regex_t regex) {
  char *buf = NULL;
  size_t len = 0;
  ssize_t read;
  while ((read = getline(&buf, &len, fp)) != -1) {
    int status = regexec(&regex, buf, 0, NULL, 0);
    if (!status) {
      printf("%s\n", file_name);
      free(buf);
      return;
    }
  }

  free(buf);
}
void grep_n(int count, char *file_name, FILE *fp, regex_t regex) {
  int i = 1;
  char *buf = NULL;
  size_t len = 0;
  ssize_t read;
  while ((read = getline(&buf, &len, fp)) != -1) {
    buf[strcspn(buf, "\n")] = '\0';
    int status = regexec(&regex, buf, 0, NULL, 0);
    if (!status) {
      if (count > 1)
        printf("%s:%d:%s\n", file_name, i, buf);
      else
        printf("%d:%s\n", i, buf);
    }
    i++;
  }

  free(buf);
}
void grep_h(FILE *fp, regex_t regex) {
  char *buf = NULL;
  size_t len = 0;
  ssize_t read;
  while ((read = getline(&buf, &len, fp)) != -1) {
    buf[strcspn(buf, "\n")] = '\0';
    int status = regexec(&regex, buf, 0, NULL, 0);
    if (!status) printf("%s\n", buf);
  }

  free(buf);
}
void grep_f(int count, char *file_name, FILE *fp, FILE *fp_template) {
  int line_count = 0;

  char *buf = NULL;
  size_t len = 0;
  ssize_t read;
  while ((read = getline(&buf, &len, fp_template)) != -1) line_count++;

  free(buf);
  buf = NULL;

  rewind(fp_template);

  regex_t *regex_array = malloc(line_count * sizeof(regex_t));

  int i = 0;
  while ((read = getline(&buf, &len, fp_template)) != -1) {
    regex_t regex;
    if (!make_template(buf, &regex)) {
      regex_array[i] = regex;
      i++;
    }
  }

  free(buf);
  buf = NULL;

  rewind(fp_template);

  int regex_array_size = i;

  int status;
  while ((read = getline(&buf, &len, fp)) != -1) {
    for (int i = 0; i < regex_array_size; i++) {
      if (!(status = regexec(&regex_array[i], buf, 0, NULL, 0))) break;
    }
    buf[strcspn(buf, "\n")] = '\0';
    if (!status) {
      if (count > 1)
        printf("%s:%s\n", file_name, buf);
      else
        printf("%s\n", buf);
    }
  }

  free(buf);

  for (int i = 0; i < regex_array_size; i++) regfree(&regex_array[i]);

  free(regex_array);
}
void grep_o(int count, char *file_name, FILE *fp, regex_t regex) {
  char *buf = NULL;
  size_t len = 0;
  ssize_t read;
  while ((read = getline(&buf, &len, fp)) != -1) {
    buf[strcspn(buf, "\n")] = '\0';
    int maxMatches = 10;
    regmatch_t matches[maxMatches];

    int position = 0;
    int printed_file_name = 0;
    while (!regexec(&regex, buf + position, maxMatches, matches, 0)) {
      if (matches[0].rm_so == -1) break;

      if (count > 1) {
        if (!printed_file_name) {
          printf("%s:%.*s\n", file_name,
                 (int)(matches[0].rm_eo - matches[0].rm_so),
                 buf + position + matches[0].rm_so);
          printed_file_name = 1;
        } else
          printf("%.*s\n", (int)(matches[0].rm_eo - matches[0].rm_so),
                 buf + position + matches[0].rm_so);
      } else
        printf("%.*s\n", (int)(matches[0].rm_eo - matches[0].rm_so),
               buf + position + matches[0].rm_so);

      position += matches[0].rm_eo;
    }
  }

  free(buf);
}