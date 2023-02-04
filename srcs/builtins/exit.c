/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 07:19:45 by mlakenya          #+#    #+#             */
/*   Updated: 2023/02/04 17:45:45 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strisnum(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	if (ft_strncmp(str, "9223372036854775807", 10000000) > 0)
		return (0);
	if (str[0] == '-' && ft_strncmp(str + 1, "9223372036854775808", 100000) > 0)
		return (0);
	return (1);
}

void	mini_exit(t_mini *mini, char **cmd, int needToExit)
{
	if (cmd[1] && cmd[2] && ft_strisnum(cmd[1]) == 0)
	{
		mini->ret = 1;
		ft_putstr_fd("exit\n", STDERR);
		ft_putendl_fd("minishell: exit: too many arguments", STDERR);
		return ;
	}
	else if (cmd[1] && ft_strisnum(cmd[1]) == 0)
	{
		mini->ret = 2;
		ft_putstr_fd("minishell: exit: ", STDERR);
		ft_putstr_fd(cmd[1], STDERR);
		ft_putendl_fd(": numeric argument required", STDERR);
	}
	else if (cmd[1])
		mini->ret = ft_atoi(cmd[1]);
	else
		mini->ret = 0;
	if (needToExit)
		print_error_exit(mini, NULL, NULL, "exit");
}
