#ifndef CAT_REALIZATION_H
#define CAT_REALIZATION_H

#include <stdio.h>

void cat(char **file_names, int count, char *option);

void cat_b(FILE *fp);
void cat_e(char *option, FILE *fp);
void cat_n(FILE *fp);
void cat_s(FILE *fp);
void cat_t(char *option, FILE *fp);
void cat_without_flag(FILE *fp);

#endif /* CAT_REALIZATION_H */
