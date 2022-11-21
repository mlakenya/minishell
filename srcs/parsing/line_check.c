/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 13:30:06 by mlakenya          #+#    #+#             */
/*   Updated: 2022/11/21 04:21:44 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
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
	{
		minishell->err_msg = ft_strjoin("minishell: syntax error: ",
				"unclosed quote");
		if (!minishell->err_msg)
			print_error_exit(minishell, NULL, NULL, strerror(errno));
		return (1);
	}
	return (0);
}

int		check_line(t_token *token)
{
	while (token)
	{
		if (is_types(token, "TAI")
		&& (!token->next || is_types(token->next, "TAIPE")))
		{
			ft_putstr_fd("bash: syntax error near unexpected token `", STDERR);
			token->next ? ft_putstr_fd(token->next->val, STDERR) : 0;
			token->next ? 0 : ft_putstr_fd("newline", STDERR);
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
