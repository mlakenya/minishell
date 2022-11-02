/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 20:05:09 by mlakenya          #+#    #+#             */
/*   Updated: 2022/10/25 20:06:20 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	len;

	j = 0;
	while (src[j])
		j++;
	i = 0;
	while (dstsize && dst[i] && i < dstsize)
		i++;
	len = i + j;
	j = 0;
	while (dstsize && src[j] && i < dstsize - 1)
		dst[i++] = src[j++];
	if (i < dstsize)
		dst[i] = '\0';
	return (len);
}
