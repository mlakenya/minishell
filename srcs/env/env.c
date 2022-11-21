/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:29:14 by mlakenya          #+#    #+#             */
/*   Updated: 2022/11/21 13:48:20 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**save_path(t_var *mini_path)
{
	char	**path_array;
	char	*path_str;
	int		i;

	if (!mini_path)
		return (NULL);
	path_array = ft_split(mini_path->value, ':');
	if (!path_array)
		return (NULL);
	i = -1;
	while (path_array[++i])
	{
		path_str = ft_strjoin(path_array[i], "/");
		if (!path_str)
		{
			free_array((void **)path_array);
			return (NULL);
		}
		free(path_array[i]);
		path_array[i] = path_str;
	}
	return (path_array);
}

void	remove_oldpwd_value(t_var *mini_env)
{
	t_var	*oldpwd;

	oldpwd = find_list(mini_env, "OLDPWD");
	if (oldpwd)
	{
		free(oldpwd->value);
		oldpwd->value = (char *)malloc(1);
		if (!oldpwd->value)
			return ;
		oldpwd->value[0] = 0;
	}
}

t_var	*init_node_mini_env(char *env)
{
	t_var	*node_env;
	int		i;

	i = 0;
	node_env = (t_var *)malloc(sizeof(t_var));
	if (!node_env)
		return (NULL);
	while (env[i] != '=' && env[i])
		i++;
	node_env->name = ft_substr(env, 0, i);
	node_env->value = ft_substr(env, i + 1, ft_strlen(env) - i + 1);
	node_env->next = NULL;
	return (node_env);
}

void	add_env_end(t_var **head, t_var **nd_add, t_var **nd_last)
{
	if (!*head)
		*head = *nd_add;
	else
	{
		if (!(*head)->next)
			(*head)->next = *nd_add;
		else
			(*nd_last)->next = *nd_add;
		(*nd_last) = *nd_add;
	}
}

t_var	*save_env(char **env)
{
	t_var	*mini_env;
	t_var	*node_env;
	t_var	*node_last;
	int		i;

	mini_env = NULL;
	node_last = NULL;
	i = 0;
	while (env[i])
	{
		if (env[i][0] == '\0')
			continue ;
		node_env = init_node_mini_env(env[i]);
		if (!node_env)
			if (!free_env_list(mini_env))
				return (NULL);
		add_env_end(&mini_env, &node_env, &node_last);
		i++;
	}
	return (mini_env);
}
