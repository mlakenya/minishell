/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 14:57:13 by mlakenya          #+#    #+#             */
/*   Updated: 2022/12/03 15:33:17 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*prev_sep(t_token *token, int skip)
{
	if (token && skip)
		token = token->prev;
	while (token && token->type < TRUNC)
		token = token->prev;
	return (token);
}

int	is_last_valid_arg(t_token *token)
{
	t_token	*prev;

	if (!token || token->type == CMD || token->type == ARG)
	{
		prev = prev_sep(token, 0);
		if (!prev || prev->type == PIPE)
			return (1);
		return (0);
	}
	else
		return (0);
}

void	squish_args2(t_mini *mini, t_token *prev, t_token **token)
{
	prev = prev_sep(*token, 0);
	if ((*token)->type == ARG && prev && !is_types((*token)->prev, "TAI")
		&& (prev->type == TRUNC || prev->type == APPEND || prev->type == INPUT))
	{
		while (is_last_valid_arg(prev) == 0)
			prev = prev->prev;
		(*token)->prev->next = (*token)->next;
		if ((*token)->next)
			(*token)->next->prev = (*token)->prev;
		(*token)->prev = prev;
		if (prev)
			(*token)->next = prev->next;
		else
			(*token)->next = mini->start_tock;
		if (!prev)
			prev = *token;
		prev->next->prev = *token;
		if (mini->start_tock->prev)
			prev->next = prev->next;
		else
			prev->next = *token;
		if (mini->start_tock->prev)
			mini->start_tock = mini->start_tock->prev;
	}
	*token = (*token)->next;
}

void	squish_args(t_mini *mini)
{
	t_token	*token;

	token = mini->start_tock;
	while (token)
	{
		squish_args2(mini, NULL, &token);
	}
}

void	arg_type(t_token *token)
{
	if (ft_strncmp(token->val, "", 1) == 0)
		token->type = EMPTY;
	else if (ft_strncmp(token->val, ">", 2) == 0)
		token->type = TRUNC;
	else if (ft_strncmp(token->val, ">>", 2) == 0)
		token->type = APPEND;
	else if (ft_strncmp(token->val, "<", 2) == 0)
		token->type = INPUT;
	else if (ft_strncmp(token->val, "<<", 2) == 0)
		token->type = HEREDOC;
	else if (ft_strncmp(token->val, "|", 2) == 0)
		token->type = PIPE;
	else if (token->prev == NULL || token->prev->type == PIPE)
		token->type = CMD;
	else
		token->type = ARG;
}
