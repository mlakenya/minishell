/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 20:04:26 by mlakenya          #+#    #+#             */
/*   Updated: 2022/11/20 22:24:05 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_lstadd_back(t_lst **lst, t_lst *new)
{
	t_lst	*begin;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	begin = (*lst);
	while (begin->next && new)
		begin = begin->next;
	begin->next = new;
}
