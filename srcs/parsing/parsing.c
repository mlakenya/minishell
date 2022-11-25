/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 19:12:20 by mlakenya          #+#    #+#             */
/*   Updated: 2022/11/21 05:09:06 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//---------------------Checking is string of commands if correct----------------

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

int	check_quotes(char *s)
{
	if (quotes(s, 2147483647))
	{
		ft_putendl_fd("minishell: syntax error with open quotes", STDERR);
		free(s);
		return (0);
	}
	return (1);
}

//-------------------------------Squish args------------------------------------

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

void	squish_args(t_mini *mini)
{
	t_token	*token;
	t_token	*prev;

	token = mini->start_tock;
	while (token)
	{
		prev = prev_sep(token, 0);
		if (token->type == ARG && prev && (prev->type == TRUNC
				|| prev->type == APPEND || prev->type == INPUT))
		{
			while (is_last_valid_arg(prev) == 0)
				prev = prev->prev;
			token->prev->next = token->next;
			if (token->next)
				token->next->prev = token->prev;
			token->prev = prev;
			if (prev)
				token->next = prev->next;
			else
				token->next = mini->start_tock;
			if (!prev)
				prev = token;
			prev->next->prev = token;
			if (mini->start_tock->prev)
				prev->next = prev->next;
			else
				prev->next = token;
			if (mini->start_tock->prev)
				mini->start_tock = mini->start_tock->prev;
		}
		token = token->next;
	}
}

//------------------------------------------------------------------------------

int	count_seps(char *s)
{
	int	seps;
	int	i;

	seps = 0;
	i = 0;
	while (s[i])
	{
		if (is_separator(s, i))
			seps++;
		i++;
	}
	return (seps);
}

char	*add_spaces(char *s)
{
	int		i;
	int		j;
	char	*s_spcs;

	i = 0;
	j = 0;
	s_spcs = (char *)malloc(ft_strlen(s) + count_seps(s) * 2 + 1);
	if (!s_spcs)
		return (NULL);
	while (s[i])
	{
		if (quotes(s, i) == 0 && is_separator(s, i))
		{
			s_spcs[j++] = ' ';
			s_spcs[j++] = s[i++];
			if (quotes(s, i) == 0 && s[i] == s[i - 1])
				s_spcs[j++] = s[i++];
			s_spcs[j++] = ' ';
		}
		else
			s_spcs[j++] = s[i++];
	}
	s_spcs[j] = 0;
	free(s);
	return (s_spcs);
}

void	arg_type(t_token *token)
{
	if (ft_strncmp(token->val, "", ft_strlen(token->val)) == 0)
		token->type = EMPTY;
	else if (ft_strncmp(token->val, ">", ft_strlen(token->val)) == 0)
		token->type = TRUNC;
	else if (ft_strncmp(token->val, ">>", ft_strlen(token->val)) == 0)
		token->type = APPEND;
	else if (ft_strncmp(token->val, "<", ft_strlen(token->val)) == 0)
		token->type = INPUT;
	else if (ft_strncmp(token->val, "<<", ft_strlen(token->val)) == 0)
		token->type = HEREDOC;
	else if (ft_strncmp(token->val, "|", ft_strlen(token->val)) == 0)
		token->type = PIPE;
	else if (token->prev == NULL || token->prev->type >= TRUNC)
		token->type = CMD;
	else
		token->type = ARG;
}

t_token	*get_next_token(char *s, int *i)
{
	char	*value;
	int		start;

	start = *i;
	while (s[*i] && s[*i] != ' ')
		(*i)++;
	value = (char *)malloc(*i + 1 - start);
	if (value == NULL)
		return (NULL);
	ft_strlcpy(value, s + start, *i + 1 - start);
	return (create_token(value));
}

t_token	*parse_str(char **s, t_mini *m)
{
	int		i;
	t_token	*prev;
	t_token	*next;

	if (!check_quotes(*s))
		return (NULL);
	replace_variables(s, m);
	if (is_variable(*s, m))
		return (NULL);
	i = 0;
	prev = NULL;
	while ((*s)[i])
	{
		skip_spaces(*s, &i);
		next = get_next_token(*s, &i);
		next->prev = prev;
		if (prev)
			prev->next = next;
		arg_type(next);
		prev = next;
	}
	if (prev)
	{
		prev->next = NULL;
		while (prev->prev)
			prev = prev->prev;
	}
	return (prev);
}

void	get_tokens(t_mini *mini)
{
	char	*line;
	t_token	*token;

	line = ft_strdup(mini->cmd_line);
    if (!line)
    {
        return (print_error_no_exit(NULL, NULL, "Can`t allocate memory"));
    }
	line = add_spaces(line);
	mini->start_tock = parse_str(&line, mini);
	free(line);
	if (!handle_heredocs(mini))
		return (clear_tokens(mini));
	squish_args(mini);
	token = mini->start_tock;
	while (token)
	{
		if (token->type == ARG)
			arg_type(token);
		token = token->next;
	}
}
