/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:28:26 by mlakenya          #+#    #+#             */
/*   Updated: 2022/12/07 17:04:41 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	print_error(int error, const char *arg)
{
	int		i;

	if (error == -1)
		ft_putstr_fd("export: not valid in this context: ", STDERR);
	else if (error == 0 || error == -3)
		ft_putstr_fd("export: not a valid identifier: ", STDERR);
	i = 0;
	while (arg[i] && (arg[i] != '=' || error == -3))
	{
		write(STDERR, &arg[i], 1);
		i++;
	}
	write(STDERR, "\n", 1);
	return (ERROR);
}

int	add_or_replace_env(char *name, char *value, t_mini *mini)
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
	var = mini->env;
	var = add_var(var, name, value);
	if (!var)
		return (-1);
	return (1);
}

int	env_add(const char *s, t_mini *mini)
{
	char	*name;
	char	*value;
	int		i;

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
	return (add_or_replace_env(name, value, mini));
}

int	ft_export(char **args, t_mini *mini)
{
	int		error_ret;

	if (!args[1])
	{
		print_sorted_env(mini);
		return (SUCCESS);
	}
	else
	{
		error_ret = is_valid_env(args[1]);
		if (args[1][0] == '=')
			error_ret = -3;
		if (error_ret <= 0)
			return (print_error(error_ret, args[1]));
		if (error_ret != 2)
			env_add(args[1], mini);
	}
	return (SUCCESS);
}
