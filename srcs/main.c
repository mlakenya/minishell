/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:57:36 by mlakenya          #+#    #+#             */
/*   Updated: 2022/11/04 20:23:00 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig	g_signals;

void	init_mini(t_mini *m)
{
	m->start_tock = 0;
}

int	main(void)
{
	t_mini	m;

	init_mini(&m);
	// signal(SIGINT, &sigint);
	// signal(SIGQUIT, &sigquit);
	get_command(&m);
}
