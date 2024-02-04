#ifndef GREP_REALIZATION_H
#define GREP_REALIZATION_H

#include <regex.h>
#include <stdio.h>

int make_template(char *input_template, regex_t *regex);
void grep(char **file_names, int count, char *option, regex_t regex,
          char *template);
void grep_e(int count, char *file_name, FILE *fp, regex_t regex);
void grep_i(int count, char *file_name, FILE *fp, char *template);
void grep_v(int count, char *file_name, FILE *fp, regex_t regex);
void grep_c(int count, char *file_name, FILE *fp, regex_t regex);
void grep_l(char *file_name, FILE *fp, regex_t regex);
void grep_n(int count, char *file_name, FILE *fp, regex_t regex);
void grep_h(FILE *fp, regex_t regex);
void grep_o(int count, char *file_name, FILE *fp, regex_t regex);
void grep_f(int count, char *file_name, FILE *fp, FILE *fp_template);

#endif /* GREP_REALIZATION_H */