/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 20:04:39 by mlakenya          #+#    #+#             */
/*   Updated: 2022/11/20 22:24:05 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

t_lst	*ft_lstlast(t_lst *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}
