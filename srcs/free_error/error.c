/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 08:24:59 by mlakenya          #+#    #+#             */
/*   Updated: 2022/12/03 14:50:36 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_error_no_exit(char *name, char *flag, char *err)
{
	if (name)
		ft_putstr2_fd(name, ": ", STDERR_FILENO);
	if (flag)
		ft_putstr2_fd(flag, ": ", STDERR_FILENO);
	if (err)
		ft_putstr2_fd(err, "\n", STDERR_FILENO);
}

void	print_error_exit(t_mini *minishell, char *name, char *flag, char *err)
{
	int	exit_status;

	exit_status = minishell->exit_status;
	print_error_no_exit(name, flag, err);
	free_tocken_add_history(minishell);
	append_history_file(minishell);
	free_minishell(minishell);
	exit(exit_status);
}

void	init_error(t_mini *minishell)
{
	if (!minishell)
		print_error_exit(minishell, "Environment init: ", NULL,
			strerror(errno));
	else
	{
		if (!minishell->env)
			print_error_exit(minishell, "Environment init: ",
				"environment saving error: ", strerror(errno));
		if (!minishell->hist_file)
			print_error_exit(minishell, "Environment init: ",
				"history file error: ", strerror(errno));
	}
}
