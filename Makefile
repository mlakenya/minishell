# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/26 15:36:00 by mlakenya          #+#    #+#              #
#    Updated: 2022/11/07 23:34:22 by mlakenya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

HEDEAR	= includes/minishell.h

PARSING	= parsing utils

VARS	= variables variables2

SIGNAL	= signal

MAIN	= main

SRCS	= $(addsuffix .c, $(addprefix srcs/parsing/, $(PARSING))) \
		  $(addsuffix .c, $(addprefix srcs/, $(MAIN))) \
		  $(addsuffix .c, $(addprefix srcs/parsing/, $(VARS))) \
		  $(addsuffix .c, $(addprefix srcs/, $(SIGNAL)))

OBJ		= $(SRCS:%.c=%.o)

LIBFT	= -L libft -lft

READL	= -lreadline

GCC		= gcc

CFLAGC	= -g -Wall -Wextra -Werror -I includes/ -I libft/  -I/Users/klemongr/.brew/opt/readline/include

all:		$(NAME)

$(NAME):	$(OBJ) $(HEDEAR)
	@make -C libft/
	$(GCC) $(OBJ) -o $(NAME) $(LIBFT) $(READL)

%.o : %.c	$(HEDEAR)
	$(GCC) $(CFLAGC) -c $< -o $@

clean:
	@make clean -C libft/
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)
	
re: fclean all

test: re 
	@make clean	
	@clear

.PHONY : all clean fclean re