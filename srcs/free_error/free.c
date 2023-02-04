/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:32:12 by mlakenya          #+#    #+#             */
/*   Updated: 2023/02/03 21:55:05 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env_node(t_var *node)
{
	if (node)
	{
		if (node->name)
			free(node->name);
		if (node->value)
			free(node->value);
		free(node);
	}
}

int	free_mini_list(t_var *head)
{
	t_var	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free_env_node(tmp);
	}
	return (0);
}

void	free_hist_node(t_hist *node)
{
	if (node->line)
		free(node->line);
	free(node);
}

int	free_hist_list(t_hist *head)
{
	t_hist	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free_hist_node(tmp);
	}
	return (0);
}

int	free_minishell(t_mini *minishell)
{
	if (minishell)
	{
		close_fds(minishell);
		ft_close(minishell->stdin);
		ft_close(minishell->stdout);
		if (minishell->env)
			free_mini_list(minishell->env);
		if (minishell->start_tock)
			clear_tokens(minishell);
		if (minishell->history)
			free_hist_list(minishell->history);
		if (minishell->hist_file)
			free(minishell->hist_file);
		if (minishell->hd_file)
			free(minishell->hd_file);
		if (minishell->cmd_line)
			free(minishell->cmd_line);
		if (minishell->err_msg)
			free(minishell->err_msg);
		if (minishell->variables)
			clear_variables(minishell);
		free(minishell);
	}
	rl_clear_history();
	return (0);
}
