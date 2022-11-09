/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 22:49:54 by mlakenya          #+#    #+#             */
/*   Updated: 2022/11/08 19:21:13 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_variable(char *s, t_mini *m, int len)
{
	t_variable	*var;
	char		*str;

	var = m->variables;
	while (var && len)
	{
		if (ft_strncmp(s, var->name, len) == 0)
			return (ft_strdup(var->value));
		var = var->next;
	}
	str = (char *)malloc(1);
	if (!str)
		return (NULL);
	str[0] = 0;
	return (str);
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

int	replace(char **s, int *start, t_mini *mini)
{
	char	*replace;
	char	*new;
	int		j;

	j = *start;
	(*start)++;
	while ((*s)[*start] && !is_determinator(*s, *start))
		(*start)++;
	replace = find_variable(*s + j + 1, mini, *start - j - 1);
	if (!replace)
		return (0);
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
