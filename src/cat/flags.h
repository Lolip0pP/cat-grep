#ifndef CAT_S21_FLAGS_H
#define CAT_S21_FLAGS_H

#include <getopt.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct {
  int number, number_non_blank, squeeze_blank, show_ends, show_tabs,
      show_non_printing;
} Flags;

Flags parse_flags(int argc, char **argv);

#endif
