#include "flags.h"

Flags parse_flags(int argc, char **argv) {
  static struct option long_opts[] = {
      {"number-nonblank", 0, NULL, 'b'},
      {"number", 0, NULL, 'n'},
      {"squeeze-blank", 0, NULL, 's'},
      {"show-nonprinting", 0, NULL, 'v'},
      {"show-ends", 0, NULL, 'E'},
      {"show-tabs", 0, NULL, 'T'},
      {0, 0, 0, 0},
  };

  int option = getopt_long(argc, argv, "beEnstTv", long_opts, NULL);
  Flags flags = {0};

  for (; option != -1;
       option = getopt_long(argc, argv, "beEnstTv", long_opts, NULL)) {
    switch (option) {
      case 'b':
        flags.number_non_blank = 1;
        break;
      case 'E':
        flags.show_ends = 1;
        break;
      case 'e':
        flags.show_ends = 1;
        flags.show_non_printing = 1;
        break;
      case 'n':
        flags.number = 1;
        break;
      case 's':
        flags.squeeze_blank = 1;
        break;
      case 'T':
        flags.show_tabs = 1;
        break;
      case 't':
        flags.show_tabs = 1;
        flags.show_non_printing = 1;
        break;
      case 'v':
        flags.show_non_printing = 1;
        break;
    }
  }

  return flags;
}
