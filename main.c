/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:57:36 by mlakenya          #+#    #+#             */
/*   Updated: 2023/02/05 16:18:24 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_sig	g_signals;

int	main(int ac, char **av, char **env)
{
	t_mini	*mini;

	(void)av;
	(void)ac;
	mini = init_mini(env);
	init_error(mini);
	loop_read(mini, NULL);
	return (free_minishell(mini));
}
