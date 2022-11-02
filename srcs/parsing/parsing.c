/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 19:12:20 by mlakenya          #+#    #+#             */
/*   Updated: 2022/11/02 21:41:58 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_quotes(char *line)
{
	int	quote;
	int	i;

	quote = 0;
	while (line[i])
	{
		if (line[i] == '\"' && quote == 0)
			quote = 1;
		else if (line[i] == '\"' && quote == 1)
			quote = 0;
		else if (line[i] == '\'' && quote == 0)
			quote = 2;
		else if (line[i] == '\'' && quote == 2)
			quote = 0;
	}
	if (quote != 0)
	{
		ft_putendl_fd("minishell: syntax error with open quotes", STDERR);
		free(line);
		return (1);
	}
}

int	is_redirection(char *s, int i)
{
	if (s[i] == '>')
		return (1);
	if (s[i] == '>' && s[i - 1] == ' ' && (s[i + 1] && s[i + 1] == ' ' || !s[i + 1]))
}

t_token	*get_next_token(char *s)
{
	t_token	*new_token;
	int		i;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	i = 0;
	while(s[i])
	{
		if (i > 0 && is_redirection(s, i))
	}
}

void	arg_type(t_token	*token)
{
	if (ft_strncmp(token->val, "", ft_strlen(token->val)) == 0)
		token->type = EMPTY;
	else if (ft_strncmp(token->val, ">", ft_strlen(token->val)) == 0)// && separator == 0)
		token->type = TRUNC;
	else if (ft_strncmp(token->val, ">>", ft_strlen(token->val)) == 0)// && separator == 0)
		token->type = APPEND;
	else if (ft_strncmp(token->val, "<", ft_strlen(token->val)) == 0)// && separator == 0)
		token->type = INPUT;
	else if (ft_strncmp(token->val, "|",  ft_strlen(token->val)) == 0)// && separator == 0)
		token->type = PIPE;
	else if (token->prev == NULL || token->prev->type >= TRUNC)
		token->type = CMD;
	else
		token->type = ARG;
}

t_token	*parse_str(char *s)
{
	
}

void	get_command(t_mini *mini)
{
	char	*s;

	while (1)
	{
		s = readline("minishell:) ");
		mini->start_tock = parse_str(s);
		while (mini->start_tock)
		{
			char *t = ft_itoa(mini->start_tock->type); 
			write(1, t, ft_strlen(t));
			write(1, " ", 1);
			free(t);
			mini->start_tock = mini->start_tock->next;
		}
		write(1, "\n", 1);
	}
}
