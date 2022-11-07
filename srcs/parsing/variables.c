/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 22:27:45 by mlakenya          #+#    #+#             */
/*   Updated: 2022/11/07 23:21:49 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_variable	*init_var(void)
{
	t_variable	*lst;

	lst = (t_variable *) malloc(sizeof(t_variable));
	if (!lst)
		return (NULL);
	lst->name = "";
	lst->value = "";
	lst->next = NULL;
	return (lst);
}

t_variable	*add_var(t_variable *lst, char *name, char *value)
{
	t_variable	*temp;

	temp = (t_variable *) malloc(sizeof(t_variable));
	if (!temp)
		return (NULL);
	lst->next = temp;
	temp->name = name;
	temp->value = value;
	return (temp);
}

t_variable	*del_var(t_variable *start, t_variable *for_del)
{
	t_variable	*temp;

	temp = start;
	while (temp->next != for_del)
		temp = temp->next;
	temp->next = NULL;
	free(for_del);
	return (temp);
}

int	is_variable(char *s, t_mini *ms)
{
	int			i;
	int			j;
	char		*name;
	char		*value;
	t_variable	*var;

	i = 0;
	while (s[i])
	{
		if (s[i] == ' ')
			return (0);
		i++;
	}
	i = 0;
	name = malloc(strlen(s));
	if (!name)
		return (-1);
	while (s[i] && s[i] != '=')
	{
		name[i] = s[i];
		i++;
	}
	name[i] = 0;
	i++;
	j = 0;
	value = malloc(strlen(s));
	if (!value)
		return (-1);
	while (s[i])
	{
		value[j] = s[i];
		i++;
		j++;
	}
	value[j] = 0;
	var = ms->variables;
	while (var != NULL)
	{
		if (strncmp(var->name, name, strlen(name)) == 0)
		{
			free (var->value);
			free (name);
			var->value = value;
			return (1);
		}
		var = var->next;
	}
	var = ms->variables;
	while (var->next != NULL)
		var = var->next;
	var = add_var(var, name, value);
	if (!var)
		return (-1);
	return (1);
}
