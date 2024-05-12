#ifndef GREP_FLAGS_S21_GREP_FLAGS_H
#define GREP_FLAGS_S21_GREP_FLAGS_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>

typedef struct {
  int regexp, ignore_case, invert_match, count, files_with_matches, line_number,
      no_filename, file, no_message, only_matching;
  char *pattern;
  int len_pattern;
  int mem_pattern;
  int n_patterns;
  int files_count;
} Flags;

Flags parse_flags(int, char **);

#endif
