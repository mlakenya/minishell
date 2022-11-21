/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 09:53:05 by mlakenya          #+#    #+#             */
/*   Updated: 2022/11/21 14:04:52 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **args, t_mini *mini)
{
	int		i;
	char	*s;
	
	if (!(args[1]))
		return (SUCCESS);
	i = 1;
	while (args[i])
	{
		s = ft_strjoin(args[i], "=");
		if (!s)
			return (ERROR);
		is_variable(s, mini);
		i++;
	}
	return (SUCCESS);
}
