# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jubarbie <jubarbie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/10/30 16:51:35 by jubarbie          #+#    #+#              #
#    Updated: 2016/04/09 08:24:32 by jubarbie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS= -ILibs/libft -ILibs/libmlx -IIncludes -Wall -Wextra -Werror
SRC=	Sources/main.c \
		Sources/fdf.c \
		Sources/line.c \
		Sources/get_next_line.c \
		Sources/init.c
OBJ=$(SRC:.c=.o)
NAME=fdf

$(NAME): $(OBJ)
	make -C Libs/libft
	make -C Libs/libmlx
	$(CC) -LLibs/libft/ -lft -LLibs/libmlx/ -lmlx -framework OpenGL -framework AppKit -o $@ $^

all: $(NAME)
	
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
