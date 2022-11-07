/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:57:36 by mlakenya          #+#    #+#             */
/*   Updated: 2022/11/07 23:20:20 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig	g_signals;

void	init_mini(t_mini *m)
{
	m->start_tock = 0;
	m->variables = init_var();
}

int	main(void)
{
	t_mini	m;
	t_token	*t;
	t_token	*next;

	init_mini(&m);
	signal(SIGINT, &sigint);
	signal(SIGQUIT, &sigquit);
	while (1)
	{
		get_command(&m);
		t = m.start_tock;
		while (t)
		{
			next = t->next;
			if (t->val != NULL)
				free(t->val);
			free(t);
			t = next;
		}
	}
}
