/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 20:04:44 by mlakenya          #+#    #+#             */
/*   Updated: 2022/10/26 15:22:28 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		cc;
	const unsigned char	*ss;
	size_t				i;

	cc = (unsigned char) c;
	ss = (const unsigned char *) s;
	i = 0;
	while (ss && i < n)
		if (ss[i++] == cc)
			return ((void *)&ss[--i]);
	return (NULL);
}
