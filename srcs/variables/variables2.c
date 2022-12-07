/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 22:49:54 by mlakenya          #+#    #+#             */
/*   Updated: 2022/12/05 14:24:14 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_var	*find_variable(char *s, t_mini *m, int len)
{
	t_var		*var;
	t_var		*var_env;

	var = m->variables;
	while (var && len)
	{
		if (ft_strncmp(s, var->name, len) == 0)
			return (var);
		var = var->next;
	}
	var_env = m->env;
	while (var_env && len)
	{
		if (ft_strncmp(s, var_env->name, len) == 0)
			return (var_env);
		var_env = var_env->next;
	}
	return (NULL);
}

char	*change_substr(char *src, char *rep, int st, int end)
{
	char	*new;

	new = (char *)malloc(st + ft_strlen(rep) + ft_strlen(src) - end + 1);
	if (!new)
		return (NULL);
	ft_strlcpy(new, src, st + 1);
	ft_strlcpy(new + st, rep, ft_strlen(rep) + 1);
	ft_strlcat(new + st + ft_strlen(rep), src + end, ft_strlen(src) - end + 2);
	return (new);
}

char	*handle_question(char *value, int len, t_mini *mini)
{
	if (len > 1)
		len = 1;
	if (ft_strncmp(value, "?", len + 1) == 0)
		return (ft_itoa(mini->ret));
	return (ft_strdup("\0"));
}

int	replace(char **s, int *start, t_mini *mini)
{
	char		*replace;
	char		*new;
	int			j;
	t_var		*var;

	j = *start;
	(*start)++;
	while ((*s)[*start] && !is_determinator(*s, *start))
		(*start)++;
	var = find_variable(*s + j + 1, mini, *start - j - 1);
	if (var)
		replace = ft_strdup(var->value);
	else
		replace = handle_question(*s + j + 1, *start - j - 1, mini);
	new = change_substr(*s, replace, j, *start);
	*start = j + ft_strlen(replace);
	free(replace);
	if (!new)
		return (0);
	free(*s);
	*s = new;
	return (1);
}

int	replace_variables(char **s, t_mini *m)
{
	int	i;
	int	single_brac;

	i = 0;
	single_brac = 0;
	while ((*s)[i])
	{
		if ((*s)[i] == '\'')
			single_brac = !single_brac;
		if ((*s)[i] == '$' && !single_brac)
		{
			if (!replace(s, &i, m))
				return (0);
		}
		else
		{
			i++;
		}
	}
	return (1);
}

void	clear_variables(t_mini *mini)
{
	t_var	*var;
	t_var	*tmp;

	var = mini->variables;
	while (var)
	{
		free(var->name);
		free(var->value);
		tmp = var;
		var = var->next;
		free(tmp);
	}
	mini->variables = NULL;
}
