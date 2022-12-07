/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 09:53:37 by mlakenya          #+#    #+#             */
/*   Updated: 2022/12/07 17:26:40 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_question(char *value, int len, t_mini *mini)
{
	if (len > 1)
		len = 1;
	if (ft_strncmp(value, "?", len + 1) == 0)
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

void	loop_read(t_mini *mini)
{
	char	*line;

	read_history_file(mini);
	while (1)
	{
		sig_init();
		line = readline("minishell$ ");
		if (!line)
			print_error_exit(mini, NULL, NULL, strerror(errno));
		if (*line != '\0' && *line != '\n')
		{
			mini->cmd_line = line;
			if (!quote_error_check(mini))
			{
				get_tokens(mini);
				if (mini->start_tock && check_line(mini->start_tock))
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
