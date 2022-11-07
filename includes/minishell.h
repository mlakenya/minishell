/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:05:45 by mlakenya          #+#    #+#             */
/*   Updated: 2022/11/07 23:22:39 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/dir.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# ifndef BUFF_SIZE
#  define BUFF_SIZE 42
# endif

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define EMPTY 0
# define CMD 1
# define ARG 2
# define TRUNC 3
# define APPEND 4
# define INPUT 5
# define PIPE 6

typedef struct s_sig
{
	int				sigint;
	int				sigquit;
	int				exit_status;
	pid_t			pid;
}				t_sig;

typedef struct s_token
{
	char			*val;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_variable
{
	char				*name;
	char				*value;
	struct s_variable	*next;
}				t_variable;

typedef struct s_mini
{
	t_token		*start_tock;
	t_variable	*variables;
}				t_mini;

/*
* get_next_line
*/
char	*get_next_line(int fd);

/*
* signal
*/
void	sigint(int code);
void	sigquit(int code);

/*
* parsing
*/
void	get_command(t_mini *mini);
int		is_determinator(char *s, int i);
void	skip_spaces(char *str, int *i);

/*
* variables
*/
int			is_variable(char *s, t_mini *ms);
int			replace_variables(char **s, t_mini *m, int i, int single_brac);
t_variable	*init_var(void);

#endif
