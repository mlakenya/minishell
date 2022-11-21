/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 22:30:00 by mlakenya          #+#    #+#             */
/*   Updated: 2022/11/21 03:33:09 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *error)
{
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
}

int	check_errors(t_token *token)
{
	char	*s;

	if (!token->next)
	{
		ft_error("zsh: parse error near \'\n\'");
		return (1);
	}
	if (token->next->type != ARG)
	{
		s = ft_strjoin("zsh: parse error near ", token->next->val);
		ft_error(s);
		free(s);
		return (1);
	}
	return (0);
}

int	get_next(t_token *token, char **s)
{
	char	*new_s;
	char	*tmp;

	new_s = readline(">");
	if (!new_s || !new_s[0])
		return (1);
	if (ft_strncmp(new_s, token->next->val, ft_strlen(new_s)) == 0)
	{
		free(new_s);
		return (0);
	}
	if (*s)
	{
		tmp = *s;
		*s = ft_strjoin(*s, new_s);
		free(new_s);
		free(tmp);
		tmp = *s;
		*s = ft_strjoin(*s, "\n");
		free(tmp);
	}
	else
		*s = new_s;
	return (1);
}

t_token	*heredoc(t_token *token)
{
	char	*s;
	t_token	*new;

	if (check_errors(token))
		return (NULL);
	s = NULL;
	while (get_next(token, &s))
		;
	new = create_token(s);
	if (token->prev)
		token->prev->next = new;
	new->prev = token->prev;
	if (token->next->next)
		token->next->next->prev = new;
	new->next = token->next->next;
	delete_token(token->next);
	delete_token(token);
	return (new);
}

int	handle_heredocs(t_mini *mini)
{
	t_token	*token;

	token = mini->start_tock;
	while (token && !mini->exit_status)
	{
		if (token->type == HEREDOC)
		{
			token = heredoc(token);
			if (!token)
				return (0);
		}
		token = token->next;
	}
	return (1);
}
