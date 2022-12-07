/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:59:43 by mlakenya          #+#    #+#             */
/*   Updated: 2022/12/05 17:52:24 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint(int code)
{
	(void)code;
	if (g_signals.pid == 0)
	{
		ft_putstr_fd("\n", STDERR);
		ft_putstr_fd("minishell$ ", STDERR);
	}
	else
	{
		ft_putstr_fd("\n", STDERR);
	}
	g_signals.exit_status = 130;
	g_signals.sigint = 1;
}

void	sigquit(int code)
{
	char	*nbr;

	nbr = ft_itoa(code);
	if (g_signals.pid != 0)
	{
		ft_putstr_fd("Quit: ", STDERR);
		ft_putendl_fd(nbr, STDERR);
		g_signals.exit_status = 131;
	}
	else
		ft_putstr_fd("\b\b  \b\b", STDERR);
	free(nbr);
}

void	sig_init(void)
{
	g_signals.sigint = 0;
	g_signals.pid = 0;
	g_signals.exit_status = 0;
	signal(SIGINT, &sigint);
	signal(SIGQUIT, &sigquit);
}
