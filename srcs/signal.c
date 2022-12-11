/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:59:43 by mlakenya          #+#    #+#             */
/*   Updated: 2022/12/11 15:29:16 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint_input(int code)
{
	(void)code;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signals.exit_status = 130;
}

void	sigint_exec(int code)
{
	(void)code;
	write(1, "\n", 1);
	g_signals.exit_status = 130;
	g_signals.sigint = 1;
}

void	sigquit(int code)
{
	char	*nbr;

	nbr = ft_itoa(code);
	ft_putstr_fd("Quit: ", STDERR);
	ft_putendl_fd(nbr, STDERR);
	g_signals.exit_status = 131;
	free(nbr);
}

void	sig_input(void)
{	
	g_signals.sigint = 0;
	g_signals.exit_status = 0;
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &sigint_input);
}

void	sig_exec(void)
{	
	g_signals.sigint = 0;
	g_signals.exit_status = 0;
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, sigquit);
	signal(SIGINT, &sigint_exec);
}
