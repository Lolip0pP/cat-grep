#include "hellp.h"

void patterns(Flags *flags, char *pattern) {
  if (flags->len_pattern == 0) {
    flags->pattern = malloc(1 << 10 * sizeof(char));
    *flags->pattern = '\0';
    flags->mem_pattern = 1 << 10;
  }

  int temp = flags->len_pattern + strlen(pattern);
  if (flags->mem_pattern < temp) {
    flags->pattern = realloc(flags->pattern, flags->mem_pattern * 2);
    flags->mem_pattern *= 2;
  }

  if (flags->len_pattern != 0) {
    strcat(flags->pattern, "|");
    flags->len_pattern++;
  }

  flags->len_pattern +=
      sprintf(flags->pattern + flags->len_pattern, "%s", pattern);
}

void file_patterns(Flags *flags, char *filepath, char **argv) {
  char *line = NULL;
  size_t memlen;
  int read;

  FILE *file = fopen(filepath, "rb");
  if (file != NULL) {
    for (; read = getline(&line, &memlen, file), read != -1;) {
      if (line[strlen(line) - 1] == '\n') {
        line[strlen(line) - 1] = '\0';
      }
      patterns(flags, line);
    }
  } else {
    fprintf(stderr, "%s: %s: No such file or directory\n", argv[0], filepath);
  }
  free(line);
  fclose(file);
}
