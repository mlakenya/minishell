/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_variable_by_name.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 14:28:32 by mlakenya          #+#    #+#             */
/*   Updated: 2022/12/03 14:58:56 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_var_in_list(t_mini *mini, t_var *next, char *for_del, int is_env)
{
	t_var	*prev;

	prev = NULL;
	while (next)
	{
		if (ft_strncmp(next->name, for_del, 1024) == 0)
		{
			if (prev)
				prev->next = next->next;
			else if (!is_env)
				mini->variables = next->next;
			else
				mini->env = next->next;
			free_env_node(next);
			break ;
		}
		prev = next;
		next = next->next;
	}
}

void	del_var_by_name(t_mini *mini, char *for_del)
{
	del_var_in_list(mini, mini->variables, for_del, 0);
	del_var_in_list(mini, mini->env, for_del, 1);
}
