/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 20:04:41 by mlakenya          #+#    #+#             */
/*   Updated: 2022/11/20 22:24:05 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

t_lst	*ft_lstnew(void *content)
{
	t_lst	*list;

	list = malloc(sizeof(*list));
	if (list)
	{
		list->content = content;
		list->next = NULL;
	}
	return (list);
}
