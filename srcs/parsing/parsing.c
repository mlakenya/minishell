/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 19:12:20 by mlakenya          #+#    #+#             */
/*   Updated: 2022/12/03 15:41:21 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	next_alloc(char *line, int *i)
{
	int		count;
	int		j;
	char	c;

	count = 0;
	j = 0;
	c = ' ';
	while (line[*i + j] && (line[*i + j] != ' ' || c != ' '))
	{
		if (c == ' ' && (line[*i + j] == '\'' || line[*i + j] == '\"'))
			c = line[*i + j++];
		else if (c != ' ' && line[*i + j] == c)
		{
			count += 2;
			c = ' ';
			j++;
		}
		else
			j++;
		if (line[*i + j - 1] == '\\')
			count--;
	}
	return (j - count + 1);
}

t_token	*get_next_token(char *line, int *i, int j, char c)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->val = malloc(next_alloc(line, i));
	if (!(token->val))
		return (NULL);
	while (line[*i] && (line[*i] != ' ' || c != ' '))
	{
		if (c == ' ' && (line[*i] == '\'' || line[*i] == '\"'))
			c = line[(*i)++];
		else if (c != ' ' && line[*i] == c)
		{
			c = ' ';
			(*i)++;
		}
		else if (line[*i] == '\\' && (*i)++)
			token->val[j++] = line[(*i)++];
		else
			token->val[j++] = line[(*i)++];
	}
	token->val[j] = '\0';
	return (token);
}

t_token	*parse_str(char **s, t_mini *m)
{
	int		i;
	t_token	*prev;
	t_token	*next;

	replace_variables(s, m);
	if (is_variable(*s, m))
		return (NULL);
	i = 0;
	prev = NULL;
	while ((*s)[i])
	{
		skip_spaces(*s, &i);
		if (!(*s)[i])
			break ;
		next = get_next_token(*s, &i, 0, ' ');
		next->prev = prev;
		if (prev)
			prev->next = next;
		arg_type(next);
		prev = next;
	}
	if (prev)
		prev->next = NULL;
	first_token(&prev);
	return (prev);
}

void	get_tokens(t_mini *mini)
{
	char	*line;
	t_token	*token;

	line = ft_strdup(mini->cmd_line);
	if (!line)
		return (print_error_no_exit(NULL, NULL, "Can`t allocate memory"));
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
