##
## EPITECH PROJECT, 2025
## G-MUL-100-PAR-1-1-myhunter-40
## File description:
## Makefile
##

NAME	=	my_hunter

SRCS	=	src/main.c			\
			src/app.c			\
			src/loop.c			\
			src/window.c		\
			src/session.c		\
			src/draw.c			\
			src/ui_widgets.c	\
			src/scene_menu.c	\
			src/scene_room.c	\
			src/scene_game.c	\
			src/world.c			\
			src/ducks.c			\
			src/net_common.c	\
			src/net_host.c		\
			src/net_client.c	\
			src/net_packet.c	\
			src/ifaces.c		\
			src/utils.c

OBJS	=	$(SRCS:.c=.o)
DEPS	=	$(SRCS:.c=.d)

CC		?=	epiclang

CFLAGS	=	-Werror -Wall -Wextra
CPPFLAGS=	-I./include -MMD -MP
LDFLAGS	=	-L./lib
LDLIBS	=	-lmy -lcsfml-network -lcsfml-graphics -lcsfml-window	\
			-lcsfml-system -lm

ifeq ($(shell uname -s),Darwin)
CSFML_DIR	?=	$(shell brew --prefix csfml)
endif

ifdef CSFML_DIR
CPPFLAGS	+=	-isystem $(CSFML_DIR)/include
LDFLAGS		+=	-L$(CSFML_DIR)/lib -Wl,-rpath,$(CSFML_DIR)/lib
endif

all: $(NAME)

lib/libmy.a:
	$(MAKE) -C lib/my
	cp lib/my/include/*.h include/
	cp lib/my/libmy.a lib/

$(OBJS): | lib/libmy.a

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS) $(LDLIBS)

debug: CFLAGS += -g3
debug: re

clean:
	rm -f $(OBJS) $(DEPS)
	rm -f \#*\#

fclean: clean
	rm -f $(NAME)
	rm -f lib/libmy.a include/my.h include/my_macro_abs.h
	$(MAKE) -C lib/my fclean

re: fclean
	$(MAKE) all

-include $(DEPS)

.PHONY: all debug clean fclean re
