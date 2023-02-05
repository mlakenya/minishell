/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 09:53:37 by mlakenya          #+#    #+#             */
/*   Updated: 2023/02/05 16:18:15 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_question(char *value, int len, t_mini *mini)
{
	if (len > 1)
		len = 1;
	if (*value == '?' && (!*(value + 1) || *(value + 1) == ' '))
		return (ft_itoa(mini->ret));
	return (ft_strdup("\0"));
}

void	print_error(char *err)
{
	ft_putstr_fd(err, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	free_tocken_add_history(t_mini *minishell)
{
	clear_tokens(minishell);
	minishell->start_tock = NULL;
	if (minishell->cmd_line)
	{
		add_history_list(minishell, minishell->cmd_line);
		add_history(minishell->cmd_line);
	}
	minishell->cmd_line = NULL;
}

void	loop_read(t_mini *mini, char *line)
{
	read_history_file(mini);
	while (1)
	{
		sig_input();
		line = readline("minishell$ ");
		if (g_signals.exit_status != 0)
			mini->ret = g_signals.exit_status;
		if (!line)
			print_error_exit(mini, NULL, NULL, strerror(errno));
		if (*line != '\0' && *line != '\n')
		{
			mini->cmd_line = line;
			if (!quote_error_check(mini))
			{
				get_tokens(mini);
				if (mini->start_tock && check_line(mini, mini->start_tock))
					minishell(mini);
			}
			else
				print_error_no_exit(NULL, NULL, mini->err_msg);
			free_tocken_add_history(mini);
		}
		else
			free(line);
	}
}
