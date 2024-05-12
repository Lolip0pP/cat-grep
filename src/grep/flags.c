#include "flags.h"

#include "hellp.h"

Flags parse_flags(int argc, char **argv) {
  static struct option long_options[] = {
      {"regexp", 1, NULL, 'e'},
      {"ignore-case", 0, NULL, 'i'},
      {"invert-match", 0, NULL, 'v'},
      {"count", 0, NULL, 'c'},
      {"files-with-matches", 0, NULL, 'l'},
      {"line-number", 0, NULL, 'n'},
      {"no-filename", 0, NULL, 'h'},
      {"no-messages", 0, NULL, 's'},
      {"file", 1, NULL, 'f'},
      {"only-matching", 0, NULL, 'o'},
      {NULL, 0, NULL, 0},
  };

  Flags flags = {0};

  int option;
  for (; option = getopt_long(argc, argv, "e:ivclnhsf:o", long_options, NULL),
         option != -1;) {
    switch (option) {
      case 'e':
        flags.regexp = 1;
        patterns(&flags, optarg);
        break;
      case 'i':
        flags.ignore_case = REG_ICASE;
        break;
      case 'v':
        flags.invert_match = 1;
        break;
      case 'c':
        flags.count = 1;
        break;
      case 'l':
        flags.files_with_matches = 1;
        break;
      case 'n':
        flags.line_number = 1;
        break;
      case 'h':
        flags.no_filename = 1;
        break;
      case 's':
        flags.no_message = 1;
        break;
      case 'f':
        flags.file = 1;
        file_patterns(&flags, optarg, argv);
        break;
      case 'o':
        flags.only_matching = 1;
        break;
    }
  }

  return flags;
}
