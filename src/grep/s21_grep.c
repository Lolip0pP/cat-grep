#include "s21_grep.h"

#include "hellp.h"

int main(int argc, char **argv) {
  if (argc < 2) return 0;

  Flags flags = parse_flags(argc, argv);

  if (flags.regexp == 0 && flags.file == 0) {
    patterns(&flags, argv[optind]);
    optind += 1;
  }

  flags.files_count = argc - optind;

  for (; optind < argc; optind++) {
    FILE *file = fopen(argv[optind], "rb");

    if (file == NULL) {
      if (flags.no_message == 0) {
        fprintf(stderr, "%s: %s: No such file or directory\n", argv[0],
                argv[optind]);
      }
    } else {
      hello_grumpy(argv, file, &flags);
      fclose(file);
    }
  }
  free(flags.pattern);
  return 0;
}

void hello_grumpy(char **argv, FILE *file, Flags *flags) {
  char *line = NULL;
  regex_t re;

  regmatch_t pmatch[] = {0};
  size_t nmatch = 1;

  int error_code;
  char *error_msg = {0};

  int lines_count = 0;
  int matches_count = 0;
  size_t memlen = 0;

  error_code = regcomp(&re, flags->pattern, REG_EXTENDED | flags->ignore_case);
  if (error_code != 0) {
    regerror(error_code, &re, error_msg, strlen(error_msg));
    fprintf(stderr, "Error analyzing regular expression '%s': %s.\n",
            flags->pattern, error_msg);
    return;
  }

  int read, re_result;

  for (; read = getline(&line, &memlen, file), read != -1;) {
    lines_count++;
    int new_line_count = 1;

    re_result = regexec(&re, line, nmatch, pmatch, 0);
    if (flags->invert_match != 0) re_result = re_result ? 0 : 1;

    if (re_result == 0) {
      if (flags->count == 0 && flags->files_with_matches == 0) {
        if (flags->files_count > 1 && flags->no_filename == 0) {
          printf("%s:", argv[optind]);
        }

        if (flags->only_matching != 0 && flags->invert_match == 0) {
          char *p = line;
          new_line_count = 0;

          for (; re_result == 0;) {
            if (pmatch[0].rm_eo == pmatch[0].rm_so) {
              break;
            }

            if (flags->line_number != 0) {
              printf("%d:", lines_count);
            }

            printf("%.*s\n", (int)(pmatch[0].rm_eo - pmatch[0].rm_so),
                   p + pmatch[0].rm_so);
            p += pmatch[0].rm_eo;

            re_result = regexec(&re, p, nmatch, pmatch, REG_NOTBOL);
          }
        }

        if (flags->line_number != 0 &&
            !(flags->only_matching != 0 && flags->invert_match == 0)) {
          printf("%d:", lines_count);
        }

        if (!flags->only_matching || flags->invert_match) printf("%s", line);

        if (line[strlen(line) - 1] != '\n' && new_line_count != 0) {
          printf("\n");
        }
      }
      matches_count++;
    }
  }

  if (flags->count != 0) {
    if (flags->files_count > 1 && !flags->no_filename) {
      printf("%s:", argv[optind]);
    }

    if (flags->files_with_matches && matches_count)
      printf("1\n");
    else
      printf("%d\n", matches_count);
  }
  if (flags->files_with_matches && matches_count) {
    printf("%s\n", argv[optind]);
  }

  free(line);
  regfree(&re);
}
