/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 19:12:20 by mlakenya          #+#    #+#             */
/*   Updated: 2022/11/13 18:48:01 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//---------------------Checking is string of commands if correct----------------

int		quotes(char *line, int index)
{
	int	i;
	int	open;

	i = 0;
	open = 0;
	while (line[i] && i != index)
	{
		if (i > 0 && line[i - 1] == '\\')
			;
		else if (open == 0 && line[i] == '\"')
			open = 1;
		else if (open == 0 && line[i] == '\'')
			open = 2;
		else if (open == 1 && line[i] == '\"')
			open = 0;
		else if (open == 2 && line[i] == '\'')
			open = 0;
		i++;
	}
	return (open);
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

//------------------------------------------------------------------------------


int count_seps(char *s)
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

char	*space_line(char *line)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = (char *)malloc(ft_strlen(line) + count_seps(line) * 2 + 1);
	if (!new)
		return (NULL);
	while (new && line[i])
	{
		if (quotes(line, i) != 2 && line[i] == '$' && i && line[i - 1] != '\\')
			new[j++] = (char)(-line[i++]);
		else if (quotes(line, i) == 0 && is_separator(line, i))
		{
			new[j++] = ' ';
			new[j++] = line[i++];
			if (quotes(line, i) == 0 && line[i] == line[i - 1])
				new[j++] = line[i++];
			new[j++] = ' ';
		}
		else
			new[j++] = line[i++];
	}
	new[j] = '\0';
	free(line);
	return (new);
}

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

t_token	*get_next_token(char *s, int *i)
{
	t_token	*new_token;
	int		start;

	start = *i;
	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	while (s[*i] && s[*i] != ' ')
		(*i)++;
	new_token->val = (char *)malloc(*i + 1 - start);
	if (new_token->val == NULL)
		return (NULL);
	ft_strlcpy(new_token->val, s + start, *i + 1 - start);
	return (new_token);
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
		prev->next = NULL;
	while (prev->prev)
		prev = prev->prev;
	return (prev);
}

void	get_command(t_mini *mini)
{
	char	*s;

	s = readline("minishell:> ");
	s = space_line(s);
	if (s)
	{
		mini->start_tock = parse_str(&s, mini);
		write(1, s, ft_strlen(s));
		write(1, "\n", 1);
		free(s);
	}
	return ;
}
