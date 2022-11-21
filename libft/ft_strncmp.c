/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 20:05:16 by mlakenya          #+#    #+#             */
/*   Updated: 2022/11/21 11:53:50 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	const unsigned char	*uns_s1;
	const unsigned char	*uns_s2;

	if (!s1)
	{
		if (!s2)
			return (0);
		else
			return (s2[0]);
	}
	uns_s1 = (const unsigned char *)s1;
	uns_s2 = (const unsigned char *)s2;
	i = 0;
	while (uns_s1[i] && uns_s2[i] && i < n)
	{
		if (uns_s1[i] - uns_s2[i])
			return (uns_s1[i] - uns_s2[i]);
		i++;
	}
	if (i < n)
		return (uns_s1[i] - uns_s2[i]);
	return (0);
}
