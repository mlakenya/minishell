/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 20:05:02 by mlakenya          #+#    #+#             */
/*   Updated: 2022/10/25 20:06:22 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*cpy;

	i = 0;
	while (s1[i])
		i++;
	cpy = malloc(sizeof(*s1) * i + 1);
	while (cpy && i--)
		cpy[i + 1] = s1[i + 1];
	if (cpy && i++)
		cpy[i] = s1[i];
	return (cpy);
}
