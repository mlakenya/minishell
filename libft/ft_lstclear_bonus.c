/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 20:04:29 by mlakenya          #+#    #+#             */
/*   Updated: 2022/11/20 22:24:05 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_lstclear(t_lst **lst, void (*del)(void *))
{
	t_lst	*begin;
	t_lst	*tmp;

	if (!del)
		return ;
	begin = (*lst);
	while (begin)
	{
		del(begin->content);
		tmp = begin;
		begin = begin->next;
		free(tmp);
	}
	*lst = NULL;
}
