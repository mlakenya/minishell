/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 19:12:20 by mlakenya          #+#    #+#             */
/*   Updated: 2022/11/07 23:50:36 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//---------------------Checking is string of commands if correct----------------

int	check_quotes(char *s)
{
	int	quote;
	int	i;

	quote = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\"' && quote == 0)
			quote = 1;
		else if (s[i] == '\"' && quote == 1)
			quote = 0;
		else if (s[i] == '\'' && quote == 0)
			quote = 2;
		else if (s[i] == '\'' && quote == 2)
			quote = 0;
		i++;
	}
	if (quote != 0)
	{
		ft_putendl_fd("minishell: syntax error with open quotes", STDERR);
		free(s);
		return (0);
	}
	return (1);
}

//------------------------------------------------------------------------------

void	arg_type(t_token	*token)
{
	if (ft_strncmp(token->val, "", ft_strlen(token->val)) == 0)
		token->type = EMPTY;
	else if (ft_strncmp(token->val, ">", ft_strlen(token->val)) == 0)
		token->type = TRUNC;
	else if (ft_strncmp(token->val, ">>", ft_strlen(token->val)) == 0)
		token->type = APPEND;
	else if (ft_strncmp(token->val, "<", ft_strlen(token->val)) == 0)
		token->type = INPUT;
	else if (ft_strncmp(token->val, "|", ft_strlen(token->val)) == 0)
		token->type = PIPE;
	else if (token->prev == NULL || token->prev->type >= TRUNC)
		token->type = CMD;
	else
		token->type = ARG;
}

t_token	*get_next_token(char *s)
{
	t_token	*new_token;
	int		i;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (i > 0 && is_determinator(s, i) && s[i - 1] != s[i])
			break ;
		i++;
	}
	new_token->val = (char *)malloc(i);
	if (new_token->val == NULL)
		return (NULL);
	ft_strlcpy(new_token->val, s, i);
	return (new_token);
}

t_token	*parse_str(char *s, t_mini *m)
{
	int		i;
	t_token	*prev;
	t_token	*next;

	if (!check_quotes(s))
		return (NULL);
	replace_variables(&s, m, 0, 0);
	if (is_variable(s, m))
		return (NULL);
	i = 0;
	prev = NULL;
	while (s[i])
	{
		skip_spaces(s, &i);
		next = get_next_token(s + i);
		next->prev = prev;
		if (prev)
			prev->next = next;
		arg_type(next);
		prev = next;
		i++;
	}
	if (prev)
		prev->next = NULL;
	while (prev->prev)
		prev = prev->prev;
	return (prev);
}

void	get_command(t_mini *mini)
{
	char	*s;

	s = readline("minishell:) ");
	mini->start_tock = parse_str(s, mini);
	return ;
}
