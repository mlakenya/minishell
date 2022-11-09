/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 22:27:45 by mlakenya          #+#    #+#             */
/*   Updated: 2022/11/08 19:22:34 by mlakenya         ###   ########.fr       */
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
	while (lst->next)
		lst = lst->next;
	lst->next = temp;
	temp->name = name;
	temp->value = value;
	temp->next = NULL;
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

int	add_or_replace_var(char *name, char *value, t_mini *mini)
{
	t_variable	*var;

	var = mini->variables;
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
