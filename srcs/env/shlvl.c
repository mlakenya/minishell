/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:41:32 by mlakenya          #+#    #+#             */
/*   Updated: 2022/12/13 16:17:00 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*find_list(t_var *mini_env, char *key)
{
	t_var	*ptr;

	ptr = mini_env;
	while (ptr)
	{
		if (ptr->name && ft_strncmp(ptr->name, key, 1024) == 0)
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

void	add_mini_end(t_var **head, t_var *last)
{
	t_var	*ptr;

	if (!*head)
		*head = last;
	else
	{
		ptr = *head;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = last;
	}
}

void	increase_shlvl(t_mini *minishell)
{
	t_var	*shlvl;
	int		level;

	shlvl = find_list(minishell->env, "SHLVL");
	if (shlvl)
	{
		level = ft_atoi(shlvl->value);
		free(shlvl->value);
		shlvl->value = ft_itoa(level + 1);
		if (!shlvl->value)
			print_error_exit(minishell,
				"Environment init: ", "shell level error", strerror(errno));
	}
	else
	{
		shlvl = init_node_mini_env("SHLVL=1");
		if (!shlvl)
			print_error_exit(minishell,
				"Environment init: ", "shell level error", strerror(errno));
		add_mini_end(&minishell->env, shlvl);
	}
}

int	is_valid_env(const char *env)
{
	int		i;

	i = 0;
	if (ft_isdigit(env[i]) != 0)
		return (0);
	while (env[i] && env[i] != '=')
	{
		if (ft_isalnum(env[i]) == 0 && env[i] != '_')
			return (-1);
		i++;
	}
	if (env[i] != '=')
		return (2);
	return (1);
}
