##
## EPITECH PROJECT, 2025
## G-MUL-100-PAR-1-1-myhunter-40
## File description:
## Makefile
##

NAME = 	my_hunter

SRCS = 	src/main.c

CC = epiclang

CFLAGS = -Werror -Wall -Wextra

CPPFLAGS = -I./include -L./lib -lmy -lcsfml-graphics
# CPPFLAGS = -I./include -L./lib -lmy

all: $(NAME)

build_my_lib:
	cd lib/my && make && cp include/*.h ../../include && cp libmy.a ..

$(NAME): build_my_lib
	$(CC) $(SRCS) -o $(NAME) $(CFLAGS) $(CPPFLAGS)

clean:
	rm -f \#*\#
	rm -f include/my.h

fclean: clean
	rm -f $(NAME)
	rm -f lib/libmy.a
	cd lib/my && make fclean

re: fclean $(NAME)
