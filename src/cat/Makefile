CC = gcc -std=c11
FLAGS = -Wall -Werror -Wextra
SOURCES = flags.c s21_cat.c

all: s21_cat

s21_cat:
	$(CC) $(FLAGS) $(SOURCES) -o s21_cat
clean:
	rm s21_cat

rebuild: clean all
