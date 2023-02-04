/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:59:43 by mlakenya          #+#    #+#             */
/*   Updated: 2023/02/04 21:41:14 by mlakenya         ###   ########.fr       */
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

void	sig_input(void)
{	
	g_signals.sigint = 0;
	g_signals.exit_status = 0;
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &sigint_input);
}

void	sigquit(void)
{
	ft_putstr_fd("Quit (core dumped)\n", STDERR);
	g_signals.exit_status = 131;
}

void	sigint_exec(void)
{
	write(2, "\n", 1);
	g_signals.exit_status = 130;
}

void	sigint_exec_init(int code)
{
	(void)code;
	g_signals.sigint = 1;
}

void	sigquit_exec_init(int code)
{
	(void)code;
	g_signals.sigquit = 1;
}

void	sig_exec(void)
{	
	g_signals.sigint = 0;
	g_signals.sigquit = 0;
	g_signals.exit_status = 0;
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, sigquit_exec_init);
	signal(SIGINT, sigint_exec_init);
}
