##
## EPITECH PROJECT, 2025
## my_str_to_word_array.c
## File description:
## Makefile
##

CC = clang

CFLAGS = -Wall -Wextra -Werror

SRC	 = 	my_compute_power_rec.c \
		my_compute_square_root.c \
		my_getnbr.c \
		my_is_prime.c \
		my_putchar.c \
		my_put_nbr.c \
		my_putstr.c \
		my_revstr.c \
		my_showmem.c \
		my_showstr.c \
		my_show_word_array.c \
		my_sort_int_array.c \
		my_strcapitalize.c \
		my_strcat.c \
		my_strcmp.c \
		my_strcpy.c \
		my_str_isalpha.c \
		my_str_islower.c \
		my_str_isnum.c \
		my_str_isprintable.c \
		my_str_isupper.c \
		my_strlen.c \
		my_strlowcase.c \
		my_strncat.c \
		my_strncmp.c \
		my_strncpy.c \
		my_strstr.c \
		my_str_to_word_array.c \
		my_strupcase.c \
		my_swap.c


OBJ = $(SRC:.c=.o)

NAME = libmy.a
TEST_NAME = unit_tests
TEST_FLAGS = --coverage -lcriterion -lgcov
GCOV = llvm-cov-20 gcov

all: $(NAME) clean

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)
	make clean

clean:
	rm rm -f $(OBJ)

fclean:
	make clean
	rm -f $(NAME)
	rm -f *.out
	rm -f *.c~
	rm -f \#*\#
	rm -f $(TEST_NAME)
	rm -f *.gc*

re: fclean $(NAME)

unit_tests: CFLAGS += --coverage
unit_tests: fclean $(NAME)
	$(CC) -o $(TEST_NAME) tests/*.c -L. -lmy -I./include $(TEST_FLAGS)

tests_run: unit_tests
	./$(TEST_NAME)

check_coverage: tests_run
	gcovr --gcov-executable "$(GCOV)" --exclude tests/
	gcovr --gcov-executable "$(GCOV)" --exclude tests/ --txt-metric branch

.PHONY = all clean fclean re
