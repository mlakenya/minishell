/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 20:05:15 by mlakenya          #+#    #+#             */
/*   Updated: 2022/10/25 20:10:57 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	char			*ss;
	unsigned int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	str = malloc(sizeof(*s) * (i + 1));
	if (str)
		str[i] = '\0';
	ss = (char *) s;
	while (str && i && --i)
		str[i] = f(i, ss[i]);
	if (str)
		str[i] = f(i, ss[i]);
	return (str);
}
