/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 22:27:45 by mlakenya          #+#    #+#             */
/*   Updated: 2022/11/26 02:47:24 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_var	*init_var(void)
{
	t_var	*lst;

	lst = (t_var *) malloc(sizeof(t_var));
	if (!lst)
		return (NULL);
	lst->name = ft_strdup("");
	lst->value = ft_strdup("");
	lst->next = NULL;
	return (lst);
}

t_var	*add_var(t_var *lst, char *name, char *value)
{
	t_var	*temp;

	temp = (t_var *) malloc(sizeof(t_var));
	if (!temp)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	lst->next = temp;
	temp->name = name;
	temp->value = value;
	temp->next = NULL;
	return (temp);
}

void	del_var_by_name(t_mini *mini, char *for_del)
{
	t_var	*next;
	t_var	*prev;

	prev = NULL;
	next = mini->variables;
	while (next)
	{
		if (ft_strncmp(next->name, for_del, 1024) == 0)
		{
			if (prev)
				prev->next = next->next;
			free_env_node(next);
			break ;
		}
		prev = next;
		next = next->next;
	}
	next = mini->env;
	while (next)
	{
		if (ft_strncmp(next->name, for_del, 1024) == 0)
		{
			if (prev)
				prev->next = next->next;
			free_env_node(next);
			break ;
		}
		prev = next;
		next = next->next;
	}
}

int	add_or_replace_var(char *name, char *value, t_mini *mini)
{
	t_var	*var;

	var = find_variable(name, mini, ft_strlen(name));
	if (var)
	{
		free(var->value);
		free(name);
		var->value = value;
		return (1);
	}
	var = mini->variables;
	while (var->next != NULL)
		var = var->next;
	var = add_var(var, name, value);
	if (!var)
		return (-1);
	return (1);
}

int	is_variable(char *s, t_mini *ms)
{
	int			i;
	char		*name;
	char		*value;

	if (!s || !ft_strchr(s, '='))
		return (0);
	i = 0;
	while (s[i] && s[i] != ' ')
		i++;
	if (s[i] == ' ')
		return (0);
	name = malloc(strlen(s));
	if (!name)
		return (-1);
	i = 0;
	while (s[i] && s[i] != '=')
	{
		name[i] = s[i];
		i++;
	}
	name[i] = 0;
	i++;
	value = ft_strdup(s + i);
	return (add_or_replace_var(name, value, ms));
}
