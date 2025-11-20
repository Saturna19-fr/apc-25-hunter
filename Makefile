##
## EPITECH PROJECT, 2025
## G-MUL-100-PAR-1-1-myhunter-40
## File description:
## Makefile
##

NAME = 	my_hunter

SRCS = 	src/main.c		\
		src/display.c	\
		src/core.c		\
		src/instances.c	\
		src/utils.c		\
		src/cleanup.c

CC = epiclang

CFLAGS = -Werror -Wall -Wextra

CPPFLAGS = -I./include -L./lib

LIBS = -lmy -lcsfml-system -lcsfml-graphics -lcsfml-window
# CPPFLAGS = -I./include -L./lib -lmy

all: $(NAME)

build_my_lib:
	cd lib/my && make && cp include/*.h ../../include && cp libmy.a ..

$(NAME): build_my_lib
	$(CC) $(SRCS) -o $(NAME) $(CFLAGS) $(CPPFLAGS) $(LIBS)


debug: build_my_lib
	$(CC) $(SRCS) -o $(NAME) $(CFLAGS) $(CPPFLAGS) $(LIBS) -g3

clean:
	rm -f \#*\#
	rm -f include/my.h

fclean: clean
	rm -f $(NAME)
	rm -f lib/libmy.a
	cd lib/my && make fclean

re: fclean $(NAME)
