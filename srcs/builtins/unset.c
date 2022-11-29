/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 09:53:05 by mlakenya          #+#    #+#             */
/*   Updated: 2022/11/29 15:05:51 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_unset(char **args, t_mini *mini)
{
	int		i;

	if (!(args[1]))
		return (SUCCESS);
	i = 1;
	while (args[i])
	{
		del_var_by_name(mini, args[i]);
		i++;
	}
	return (SUCCESS);
}
