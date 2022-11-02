/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 20:05:11 by mlakenya          #+#    #+#             */
/*   Updated: 2022/10/25 20:06:20 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		if (dstsize && i < dstsize - 1)
			dst[i] = src[i];
		else if (dstsize && i == dstsize - 1)
			dst[i] = '\0';
		i++;
	}
	if (!src[i] && dstsize && i <= dstsize - 1)
		dst[i] = '\0';
	return (i);
}
