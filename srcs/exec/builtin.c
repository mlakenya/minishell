/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 04:57:36 by mlakenya          #+#    #+#             */
/*   Updated: 2022/11/29 18:00:44 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char *command)
{
	if (ft_strncmp(command, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(command, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(command, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(command, "env", 4) == 0)
		return (1);
	if (ft_strncmp(command, "export", 7) == 0)
		return (1);
	if (ft_strncmp(command, "unset", 6) == 0)
		return (1);
	return (0);
}

int	exec_builtin(char **args, t_mini *mini)
{
	int		result;

	result = 0;
	if (ft_strncmp(args[0], "echo", 4) == 0)
		result = ft_echo(args, mini);
	if (ft_strncmp(args[0], "cd", 2) == 0)
		result = ft_cd(args, mini);
	if (ft_strncmp(args[0], "pwd", 3) == 0)
		result = ft_pwd();
	if (ft_strncmp(args[0], "env", 3) == 0)
		ft_env(mini->env);
	if (ft_strncmp(args[0], "export", 6) == 0)
		ft_export(args, mini);
	if (ft_strncmp(args[0], "unset", 5) == 0)
		ft_unset(args, mini);
	return (result);
}
