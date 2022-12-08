/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 22:02:35 by mlakenya          #+#    #+#             */
/*   Updated: 2022/12/08 15:41:48 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clear_tokens(t_mini *mini)
{
	t_token	*tmp;

	while (mini->start_tock)
	{
		free(mini->start_tock->val);
		tmp = mini->start_tock;
		mini->start_tock = mini->start_tock->next;
		free(tmp);
	}
}

void	delete_token(t_token *token)
{
	if (token->val)
		free(token->val);
	free(token);
}

t_token	*create_token(char *s)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->val = s;
	if (!s)
		token->type = EMPTY;
	return (token);
}

t_token	*next_sep(t_token *token, int skip)
{
	if (token && skip)
		token = token->next;
	while (token && token->type < TRUNC)
		token = token->next;
	return (token);
}

t_token	*next_run(t_token *token, int skip)
{
	if (token && skip)
		token = token->next;
	while (token && token->type != CMD)
	{
		token = token->next;
		if (token && token->type == CMD)
			token = token->next;
	}
	return (token);
}
