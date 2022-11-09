/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 23:17:47 by mlakenya          #+#    #+#             */
/*   Updated: 2022/11/08 19:03:40 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	skip_spaces(char *str, int *i)
{
	while ((str[*i] == ' ' || str[*i] == '\t')
		|| (str[*i] == '\r' || str[*i] == '\v' || str[*i] == '\f'))
		(*i)++;
}
