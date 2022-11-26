/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 08:12:15 by mlakenya          #+#    #+#             */
/*   Updated: 2022/11/26 05:01:55 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	int	nb_args(char **args)
{
	int		size;

	size = 0;
	while (args[size])
		size++;
	return (size);
}

static	int	has_n_option(char **args, int *i)
{
	int ret;

	ret = 0;
	while (args[*i] && ft_strncmp(args[*i], "-n", 2) == 0)
	{
		ret = 1;
		(*i)++;
	}
	return (ret);
}

int	ft_echo(char **args, t_mini *mini)
{
	int		i;
	int		n_option;
	int		fd;

	fd = 1;
	if (mini->fdin != -1)
		fd = mini->fdout;
	i = 1;
	if (nb_args(args) > 1)
	{
		n_option = has_n_option(args, &i);
		while (args[i])
		{
			ft_putstr_fd(args[i], fd);
			if (args[i + 1] && args[i][0] != '\0')
				write(1, " ", 1);
			i++;
		}
	}
	if (n_option == 0)
		write(1, "\n", fd);
	return (SUCCESS);
}
