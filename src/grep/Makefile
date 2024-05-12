CC = gcc -std=c11
FLAGS = -Wall -Werror -Wextra
SOURCES = hellp.c flags.c s21_grep.c

all: s21_grep

s21_grep:
	$(CC) $(FLAGS) $(SOURCES) -o s21_grep
clean:
	rm s21_grep

rebuild: clean all
