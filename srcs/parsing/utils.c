/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 23:17:47 by mlakenya          #+#    #+#             */
/*   Updated: 2022/11/19 19:08:12 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_determinator(char *s, int i)
{
	if (s[i] == ' ')
		return (1);
	if (s[i] == '>')
		return (1);
	if (s[i] == '<')
		return (1);
	if (s[i] == '$')
		return (1);
	if (s[i] == '|')
		return (1);
	return (0);
}

int	is_separator(char *s, int i)
{
	if (s[i] == '>')
		return (1);
	if (s[i] == '<')
		return (1);
	if (s[i] == '|')
		return (1);
	return (0);
}

void	skip_spaces(char *str, int *i)
{
	while ((str[*i] == ' ' || str[*i] == '\t')
		|| (str[*i] == '\r' || str[*i] == '\v' || str[*i] == '\f'))
		(*i)++;
}

char	**free_array(void **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
	return (NULL);
}

void	remove_end_line_sign(char *str)
{
	while (*str != '\0' && *str != '\n')
		++str;
	*str = '\0';
}
