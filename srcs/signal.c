/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:59:43 by mlakenya          #+#    #+#             */
/*   Updated: 2022/11/21 18:34:40 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint(int code)
{
	(void)code;
	ft_putstr_fd("\b\b  ", STDERR);
	ft_putstr_fd("\n", STDERR);
	g_signals.exit_status = 1;
	g_signals.sigint = 1;
	return ;
}

void	sigquit(int code)
{
	(void)code;
	ft_putstr_fd("\b\b  \b\b", STDERR);
	return ;
}

void	sig_init(void)
{
	g_signals.sigint = 0;
	g_signals.pid = 0;
	g_signals.exit_status = 0;
}
