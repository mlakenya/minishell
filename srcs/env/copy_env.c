/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 11:50:35 by mlakenya          #+#    #+#             */
/*   Updated: 2023/02/05 16:26:19 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_list_len(t_var *list)
{
	t_var	*head;
	int		len;

	head = list;
	len = 0;
	while (head)
	{
		len++;
		head = head->next;
	}
	return (len);
}

char	*strjoin_env(char const *s1, char const *s2, int needQuotes)
{
	char	*ptr;
	char	*str;

	if (s1 == NULL)
		return (NULL);
	if (s2 == NULL)
		return (ft_strdup(s1));
	ptr = (char *)malloc(sizeof(char)
			* (ft_strlen(s1) + ft_strlen(s2) + 2 + needQuotes * 2));
	str = ptr;
	while (*s1 != '\0')
		*ptr++ = *s1++;
	*ptr++ = '=';
	if (needQuotes)
		*ptr++ = '"';
	while (*s2 != '\0')
		*ptr++ = *s2++;
	if (needQuotes)
		*ptr++ = '"';
	*ptr = '\0';
	return (str);
}

char	**copy_env(t_var *mini_env, int needQuotes)
{
	t_var	*ptr_env;
	char	**env_copy;
	int		len;

	if (!mini_env)
		return (NULL);
	len = env_list_len(mini_env) + 1;
	env_copy = (char **)malloc(sizeof(char *) * len);
	if (!env_copy)
		return (NULL);
	len = 0;
	ptr_env = mini_env;
	while (ptr_env)
	{
		env_copy[len] = strjoin_env(ptr_env->name, ptr_env->value, needQuotes);
		if (!env_copy[len])
			return (free_array((void **)env_copy));
		ptr_env = ptr_env->next;
		len++;
	}
	env_copy[len] = NULL;
	return (env_copy);
}

void	sort_env(char **tab, int env_len)
{
	int		ordered;
	int		i;
	char	*tmp;

	ordered = 0;
	while (tab && ordered == 0)
	{
		ordered = 1;
		i = 0;
		while (i < env_len - 1)
		{
			if (ft_strncmp(tab[i], tab[i + 1], 1024) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				ordered = 0;
			}
			i++;
		}
		env_len--;
	}
}

void	print_sorted_env(t_mini *mini)
{
	int		i;
	char	**tab;
	char	**tab_var;
	t_var	*env;

	env = mini->env;
	tab = copy_env(env, 1);
	tab_var = copy_env(mini->variables->next, 1);
	sort_env(tab, env_list_len(env));
	sort_env(tab_var, env_list_len(mini->variables->next));
	i = 0;
	while (tab && tab[i])
	{
		write(1, "declare -x ", 11);
		ft_putendl_fd(tab[i], 1);
		i++;
	}
	i = 0;
	while (tab_var && tab_var[i])
	{
		write(1, "declare -x ", 11);
		ft_putendl_fd(tab_var[i], 1);
		i++;
	}
}
