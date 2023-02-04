/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 04:48:40 by mlakenya          #+#    #+#             */
/*   Updated: 2023/02/04 13:10:04 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**cmd_tab(t_token *start, int i)
{
	t_token	*token;
	char	**tab;

	if (!start)
		return (NULL);
	token = start->next;
	while (token && token->type < TRUNC)
	{
		token = token->next;
		i++;
	}
	tab = malloc(sizeof(char *) * i);
	if (!tab)
		return (NULL);
	token = start->next;
	tab[0] = ft_strdup(start->val);
	i = 1;
	while (token && token->type < TRUNC)
	{
		tab[i++] = ft_strdup(token->val);
		token = token->next;
	}
	tab[i] = NULL;
	return (tab);
}

int	has_pipe(t_token *token)
{
	while (token)
	{
		if (is_type(token, PIPE))
			return (1);
		token = token->next;
	}
	return (0);
}

void	exec_cmd(t_mini *mini, t_token *token)
{
	char	**cmd;

	if (mini->charge == 0)
		return ;
	cmd = cmd_tab(token, 2);
	if (cmd && ft_strncmp(cmd[0], "exit", 5) == 0)
	{
		if (has_pipe(mini->start_tock) == 0)
			mini_exit(mini, cmd, 1);
		else
			mini_exit(mini, cmd, 0);
	}
	else if (cmd && is_builtin(cmd[0]))
		mini->ret = exec_builtin(cmd, mini);
	else if (cmd)
		mini->ret = exec_bin(cmd, mini->env, mini);
	free_array((void **)cmd);
	ft_close(mini->pipin);
	ft_close(mini->pipout);
	mini->pipin = -1;
	mini->pipout = -1;
	mini->charge = 0;
}

void	redir_and_exec(t_mini *mini, t_token *token)
{
	t_token	*prev;
	t_token	*next;
	int		pipe;

	prev = prev_sep(token, 0);
	next = next_sep(token, 0);
	pipe = 0;
	if (is_type(prev, TRUNC))
		redir(mini, token, TRUNC);
	if (is_type(prev, HEREDOC))
		input(mini, token, HEREDOC);
	else if (is_type(prev, APPEND))
		redir(mini, token, APPEND);
	else if (is_type(prev, INPUT))
		input(mini, token, INPUT);
	else if (is_type(prev, PIPE))
		pipe = minipipe(mini);
	if (next && pipe != 1)
		redir_and_exec(mini, next->next);
	if ((is_type(prev, PIPE) || !prev) && pipe != 1 && mini->no_exec == 0)
		exec_cmd(mini, token);
}

void	minishell(t_mini *mini)
{
	t_token	*token;
	int		status;

	sig_exec();
	token = next_run(mini->start_tock, 0);
	if (is_types(mini->start_tock, "TAI"))
		token = mini->start_tock->next;
	while (mini->exit_status == 0 && token)
	{
		mini->charge = 1;
		mini->parent = 1;
		mini->last = 1;
		redir_and_exec(mini, token);
		reset_std(mini);
		close_fds(mini);
		reset_fds(mini);
		waitpid(-1, &status, 0);
		status = WEXITSTATUS(status);
		if (mini->last == 0)
			mini->ret = status;
		if (mini->parent == 0)
			print_error_exit(mini, NULL, NULL, NULL);
		mini->no_exec = 0;
		token = next_run(token, 1);
	}
}
