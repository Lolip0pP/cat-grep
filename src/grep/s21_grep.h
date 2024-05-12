#ifndef GREP_S21_GREP_H
#define GREP_S21_GREP_H

#define _GNU_SOURCE

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "flags.h"

void hello_grumpy(char **, FILE *, Flags *);

#endif
