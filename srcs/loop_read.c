/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 09:53:37 by mlakenya          #+#    #+#             */
/*   Updated: 2022/11/21 18:34:09 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *err)
{
	ft_putstr_fd(err, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	free_tocken_add_history(t_mini *minishell)
{
	clear_tokens(minishell);
	minishell->start_tock = NULL;
	// free_mini_cmds(minishell->cmds);
	// minishell->cmds = NULL;
	add_history_list(minishell, minishell->cmd_line);
	add_history(minishell->cmd_line);
	minishell->cmd_line = NULL;
}

void	loop_read(t_mini *mini)
{
	char	*line;

	read_history_file(mini);
	while (1)
	{
		signal(SIGINT, &sigint);
		signal(SIGQUIT, &sigquit);
		line = readline("minishell$ ");
		sig_init();
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
			{
				print_error(mini->err_msg);
				mini->err_msg = NULL;
			}
			free_tocken_add_history(mini);
		}
		else
			free(line);
	}
}
 