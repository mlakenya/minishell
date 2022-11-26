# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/26 15:36:00 by mlakenya          #+#    #+#              #
#    Updated: 2022/11/26 06:20:11 by mlakenya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

HEDEAR	= includes/minishell.h gnl/get_next_line.h

PARSING	= parsing utils utils2 line_check 

HISTORY = history

HEREDOC = heredoc_utils heredoc

FREEERR = error free

ENV     = copy_env env shlvl

VARS	= variables variables2

COMMON	= signal token init loop_read

MAIN	= main 

GNL     = get_next_line get_next_line_utils

EXEC    = bin builtin exec redir fds

BUILTIN = cd echo env exit export pwd unset

SRCS	= $(addsuffix .c, $(addprefix srcs/parsing/, $(PARSING))) \
		  $(addsuffix .c, $(MAIN)) \
		  $(addsuffix .c, $(addprefix srcs/variables/, $(VARS))) \
		  $(addsuffix .c, $(addprefix srcs/, $(COMMON))) \
		  $(addsuffix .c, $(addprefix srcs/history/, $(HISTORY))) \
		  $(addsuffix .c, $(addprefix srcs/heredoc/, $(HEREDOC))) \
		  $(addsuffix .c, $(addprefix srcs/free_error/, $(FREEERR))) \
		  $(addsuffix .c, $(addprefix srcs/env/, $(ENV))) \
		  $(addsuffix .c, $(addprefix gnl/, $(GNL))) \
		  $(addsuffix .c, $(addprefix srcs/exec/, $(EXEC))) \
		  $(addsuffix .c, $(addprefix srcs/builtins/, $(BUILTIN)))

OBJ		= $(SRCS:%.c=%.o)

LIBFT	= -L libft -lft

READL	= -lreadline

GCC		= gcc

CFLAGC	= -g -Wall -Wextra -Werror -I includes/ -I libft/ -I gnl/

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