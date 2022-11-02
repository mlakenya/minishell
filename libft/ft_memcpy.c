/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 20:04:48 by mlakenya          #+#    #+#             */
/*   Updated: 2022/10/25 20:06:28 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	const char	*from;
	char		*to;

	to = (char *) dst;
	from = (const char *) src;
	i = 0;
	while (to && from && i++ < n)
		to[i - 1] = from[i - 1];
	return (dst);
}
