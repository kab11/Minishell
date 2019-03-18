# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kblack <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/02 11:59:37 by kblack            #+#    #+#              #
#    Updated: 2019/03/13 14:06:36 by kblack           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror

SRC		=	cd_command.c \
			echo_command.c \
			env_command.c \
			exit_command.c \
			free_list.c \
			main.c \
			mini_execute.c \
			mini_parse.c

INC_FT	=	-I includes/libft
LINK_FT	=	-L includes/libft -lft
FT		=	$(INC_FT) $(LINK_FT)

INC_PT	=	-I includes/ft_printf
LINK_PT	=	-L includes/ft_printf -lftprintf
PT 		=	$(INC_PT) $(LINK_PT)

OFL = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OFL)
	make -C includes/libft
	make -C includes/ft_printf
	$(CC) -o $@ $(CFLAGS) $(FT) $(PT) $(OFL) -I .

$(OFL): $(SRC)
	@$(CC) $(CFLAGS) $(INC_FT) $(INC_PT) -I . -c $(SRC)

clean:
	rm -rf $(OFL)
	make -C includes/libft clean
	make -C includes/ft_printf clean

fclean: clean
	rm -rf $(NAME)
	make -C includes/libft fclean
	make -C includes/ft_printf fclean

re: fclean all
	make -C includes/libft re
	make -C includes/ft_printf re
