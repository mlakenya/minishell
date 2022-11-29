/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:05:45 by mlakenya          #+#    #+#             */
/*   Updated: 2022/11/29 15:12:07 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"
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
# define TRUNC 4
# define APPEND 5
# define INPUT 6
# define PIPE 7
# define HEREDOC 8

# define ERROR 1
# define SUCCESS 0
# define IS_DIRECTORY 126
# define UNKNOWN_COMMAND 127

typedef struct s_sig
{
	int				sigint;
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

typedef struct s_var
{
	char			*name;
	char			*value;
	struct s_var	*next;
}				t_var;

typedef struct s_hist
{
	char			*line;
	struct s_hist	*next;
	struct s_hist	*prev;
}	t_hist;

typedef struct s_expansions
{
	char			*new_arg;
	int				i;
	int				j;
}				t_expansions;

typedef struct s_mini
{
	t_token		*start_tock;
	t_var		*variables;
	t_var		*env;
	t_hist		*history;
	char		**env_str;
	char		**path_array;
	char		*err_msg;
	char		*cmd_line;
	char		*hist_file;
	char		*hd_file;
	int			exit_status;
	int			stdin;
	int			stdout;
	int			fdin;
	int			fdout;
	int			pipin;
	int			pipout;
	int			pid;
	int			charge;
	int			parent;
	int			last;
	int			ret;
	int			no_exec;
}				t_mini;

/*
 * signal
*/
void		sigint(int code);
void		sigquit(int code);
void		sig_init(void);

/*
 * parsing
*/
void		get_tokens(t_mini *mini);
int			is_separator(char *s, int i);
int			quote_error_check(t_mini *minishell);
int			check_line(t_token *token);
void		skip_spaces(char *str, int *i);
int			is_determinator(char *s, int i);

/*
 * variables
*/
int			is_variable(char *s, t_mini *ms);
int			replace_variables(char **s, t_mini *m);
t_var		*init_var(void);
t_var		*find_variable(char *s, t_mini *m, int len);
void		clear_variables(t_mini *mini);
void		del_var_by_name(t_mini *mini, char *for_del);

/*
 * token
*/
void		clear_tokens(t_mini *mini);
void		delete_token(t_token *token);
t_token		*create_token(char *s);
t_token		*prev_sep(t_token *token, int skip);
t_token		*next_sep(t_token *token, int skip);
t_token		*next_run(t_token *token, int skip);

/*
 * errors
*/
void		init_error(t_mini *minishell);
void		print_error_exit(t_mini *minishell,
				char *name, char *flag, char *err);
void		print_error_no_exit(char *name, char *flag, char *err);

/*
 * init
*/
t_mini		*init_mini(char **env);

/*
 * loop_read
*/
void		loop_read(t_mini *mini);

/*
 * free
*/
int			free_minishell(t_mini *minishell);
char		**free_array(void **array);
int			free_mini_list(t_var *head);
void		free_env_node(t_var *node);

/*
 * env
*/
t_var		*save_env(char **env);
t_var		*init_node_mini_env(char *env);
t_var		*find_list(t_var *mini_env, char *key);
void		increase_shlvl(t_mini *minishell);
void		remove_oldpwd_value(t_var *mini_env);
char		**copy_env(t_var *mini_env);
char		**save_path(t_var *mini_path);
void		print_sorted_env(t_mini *mini);
int			is_valid_env(const char *env);

/*
 * utils
*/
void		remove_end_line_sign(char *str);
void		ft_putstr2_fd(char *s1, char *s2, int fd);
int			is_types(t_token *token, char *types);
int			is_type(t_token *token, int type);

/*
 * hitory
*/
char		*get_hist_file_name(t_mini *minishell);
void		add_history_list(t_mini *minishell, char *line);
void		append_history_file(t_mini *minishell);
void		read_history_file(t_mini *minishell);
void		free_tocken_add_history(t_mini *minishell);

/*
 * heredoc 
*/
char		*get_hd_file_name(t_mini *minishell);
int			handle_heredocs(t_mini *mini);

/*
 * exec 
*/
void		redir(t_mini *mini, t_token *token, int type);
void		input(t_mini *mini, t_token *token, int type);
int			minipipe(t_mini *mini);
void		minishell(t_mini *mini);
void		ft_close(int fd);
void		reset_std(t_mini *mini);
void		close_fds(t_mini *mini);
void		reset_fds(t_mini *mini);
int			exec_bin(char **args, t_var *env, t_mini *mini);

/*
 * builtins 
*/
int			is_builtin(char *command);
int			exec_builtin(char **args, t_mini *mini);
void		mini_exit(t_mini *mini, char **cmd);
int			ft_echo(char **args, t_mini *mini);
int			ft_export(char **args, t_var *env, t_mini *mini);
int			ft_cd(char **args, t_mini *mini);
int			ft_env(t_var *env);
int			ft_pwd(void);
int			ft_unset(char **args, t_mini *mini);

extern t_sig	g_signals;
#endif
