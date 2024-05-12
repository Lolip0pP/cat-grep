#ifndef GREP_UTILS_S21_GREP_UTILS_H
#define GREP_UTILS_S21_GREP_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "flags.h"

void patterns(Flags *, char *);
void file_patterns(Flags *, char *, char **);

#endif
