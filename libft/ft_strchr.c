/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 20:05:00 by mlakenya          #+#    #+#             */
/*   Updated: 2022/10/26 19:56:04 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	unsigned char	cc;

	if (s == NULL)
		return (NULL);
	cc = (unsigned char)c;
	i = 0;
	while (s[i])
		if (s[i++] == cc)
			return ((char *)&s[--i]);
	if (s[i] == cc)
		return ((char *)&s[i]);
	return (NULL);
}
