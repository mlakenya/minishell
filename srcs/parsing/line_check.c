/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 13:30:06 by mlakenya          #+#    #+#             */
/*   Updated: 2022/12/03 15:41:32 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	quote_error(t_mini *minishell)
{
	minishell->err_msg = ft_strjoin("minishell: syntax error: ",
			"unclosed quote");
	if (!minishell->err_msg)
		print_error_exit(minishell, NULL, NULL, strerror(errno));
	return (1);
}

int	quote_error_check(t_mini *minishell)
{
	char	*line;
	int		q_count;
	char	quote;

	line = minishell->cmd_line;
	q_count = 0;
	quote = 0;
	while (*line)
	{
		if (*line == '\'' || *line == '\"')
		{
			quote = (int)*line;
			q_count++;
			line++;
			while (*line && *line != quote)
				line++;
			if (*line == quote)
				q_count = 0;
		}
		line++;
	}
	if (q_count == 1)
		return (quote_error(minishell));
	return (0);
}

int	check_line(t_token *token)
{
	while (token)
	{
		if (is_types(token, "TAI")
			&& (!token->next || is_types(token->next, "TAIPE")))
		{
			ft_putstr_fd("bash: syntax error near unexpected token `", STDERR);
			if (token->next)
				ft_putstr_fd(token->next->val, STDERR);
			else
				ft_putstr_fd("newline", STDERR);
			ft_putendl_fd("'", STDERR);
			return (0);
		}
		if (is_types(token, "PE")
			&& (!token->prev || !token->next || is_types(token->prev, "TAIPE")))
		{
			ft_putstr_fd("bash: syntax error near unexpected token `", STDERR);
			ft_putstr_fd(token->val, STDERR);
			ft_putendl_fd("'", STDERR);
			return (0);
		}
		token = token->next;
	}
	return (1);
}

int	quotes(char *line, int index)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (line[i] && i != index)
	{
		if (quote == 0 && line[i] == '\"')
			quote = 1;
		else if (quote == 0 && line[i] == '\'')
			quote = 2;
		else if (quote == 1 && line[i] == '\"')
			quote = 0;
		else if (quote == 2 && line[i] == '\'')
			quote = 0;
		i++;
	}
	return (quote);
}
