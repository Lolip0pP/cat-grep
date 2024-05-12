#ifndef CAT_S21_CAT_H
#define CAT_S21_CAT_H

#define _GNU_SOURCE

#include <errno.h>
#include <stdio.h>

#include "flags.h"

char process_nonprinting(char ch);
void hello_kitty(FILE *, Flags *);

#endif
