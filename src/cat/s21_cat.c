#include "s21_cat.h"

int main(int argc, char **argv) {
  if (argc >= 2) {
    Flags flags = parse_flags(argc, argv);
    FILE *file = NULL;

    for (char **flag = &argv[1], **end = &argv[argc]; flag != end; flag++) {
      if (**flag == '-') continue;

      file = fopen(*flag, "r");
      if (errno) {
        fprintf(stderr, "%s: %s: No such file or directory\n", argv[0], *flag);
        continue;
      }
      hello_kitty(file, &flags);
      fclose(file);
    }
  }
  return 0;
}

char old_chars_magic(char ch) {
  if (ch == '\n' || ch == '\t') {
    return ch;
  }

  if (ch < 32) {
    putchar('^');
    ch += 64;
  } else if (ch == 127) {
    putchar('^');
    ch = '?';
  }
  return ch;
}

void hello_kitty(FILE *file, Flags *flags) {
  int prev = 1, curr = 0;
  int squeezed = 0, lines_count = 0;

  for (; file;) {
    int c = fgetc(file);
    if (c == EOF) break;
    curr = (c == '\n') ? 1 : 0;

    if (prev) {
      if (flags->squeeze_blank && curr) {
        if (squeezed)
          continue;
        else
          squeezed = 1;
      } else {
        squeezed = 0;
      }

      if (flags->number_non_blank) {
        if (!curr) {
          printf("%6i\t", ++lines_count);
        } else if (flags->show_ends) {  // remove for Linux
          printf("%6c\t", ' ');
        }

      } else if (flags->number) {
        printf("%6i\t", ++lines_count);
      }
    }

    if (flags->show_ends && c == '\n') {
      putchar('$');
    }

    if (flags->show_non_printing) {
      c = old_chars_magic(c);
    }

    if (flags->show_tabs && c == '\t') {
      putchar('^');
      c = 'I';
    }

    putchar(c);
    prev = curr;
  }
}
