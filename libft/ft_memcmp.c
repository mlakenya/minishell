/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 20:04:45 by mlakenya          #+#    #+#             */
/*   Updated: 2022/10/25 20:07:56 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*uns_s1;
	const unsigned char	*uns_s2;

	uns_s1 = (const unsigned char *) s1;
	uns_s2 = (const unsigned char *) s2;
	i = 0;
	while (uns_s1 && uns_s2 && i < n)
	{
		if (uns_s1[i] - uns_s2[i])
			return (uns_s1[i] - uns_s2[i]);
		i++;
	}
	if (i < n)
		return (uns_s1[i] - uns_s2[i]);
	return (0);
}
