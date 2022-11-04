/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 19:12:20 by mlakenya          #+#    #+#             */
/*   Updated: 2022/11/04 20:25:41 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//--------------------Replacing variables in string of commands-----------------

char	*find_variable(char *s, t_mini *m, int len)
{
	t_variable	*var;
	char		*str;

	var = m->variables;
	while (var)
	{
		if (ft_strncmp(s, var->name, len) == 0)
			return (ft_strdup(var->value));
	}
	str = (char *)malloc(1);
	if (!str)
		return (NULL);
	str[0] = 0;
	return (str);
}

char	*change_substr(char *src, char *rep, int st, int end)
{
	char	*new;

	new = (char *)malloc(st + ft_strlen(rep) + ft_strlen(src) - end + 1);
	if (!new)
		return (NULL);
	ft_strlcpy(new, src, st + 1);
	ft_strlcpy(new + st, rep, ft_strlen(rep) + 1);
	ft_strlcat(new, src + end, ft_strlen(src) - end + 1);
	free(rep);
	return (new);
}

int	replace_variables(char **s, t_mini *m, int i, int single_brac)
{
	int		j;
	char	*replace;
	char	*new;

	while ((*s)[i])
	{
		if ((*s)[i] == '\'')
			single_brac = !single_brac;
		if ((*s)[i] == '$' && !single_brac)
		{
			j = i;
			while ((*s)[i] && !is_determinator(*s, i))
				i++;
			replace = find_variable(*s + j, m, i);
			if (!replace)
				return (0);
			new = change_substr(*s, replace, j, i);
			if (!new)
				return (0);
			free(*s);
			*s = new;
		}
		i++;
	}
	return (1);
}

//-------Cheking if this token is a variable and adding it into memory----------

//--Returns 1 if this is a variable and it's added-----------------
//--0 if this is not a variable ---------------------------
//--and -1 in case of error------------------------------
int	is_variable(t_token *token, t_mini *m)
{
	int			i;
	t_variable	*new_var;
	t_variable	*iter;

	i = 0;
	while (token->val[i] && token->val[i] != '=')
		i++;
	if (i == 0 || !token->val[i])
		return (0);
	new_var = (t_variable *)malloc(sizeof(t_variable));
	if (!new_var)
		return (-1);
	new_var->name = (char *)malloc(i);
	if (new_var->name)
	{
		free(new_var);
		return (-1);
	}
	ft_strlcpy(new_var->name, token->val, i + 1);
	if (i == ft_strlen(token->val))
	{
		new_var->value = (char *)malloc(1);
	}
	else
	{
		new_var->value = (char *)malloc(ft_strlen(token->val) - i - 1);
	}
	if (!new_var->value)
	{
		free(new_var->name);
		free(new_var);
		return (-1);
	}
	ft_strlcpy(new_var->value, token->val, ft_strlen(token->val) - i + 1);
	if (!m->variables)
		m->variables = new_var;
	else
	{
		iter = m->variables;
		while (iter->next)
			iter = iter->next;
		iter->next = new_var;
	}
	return (1);
}

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

int	is_determinator(char *s, int i)
{
	if (s[i] == ' ')
		return (1);
	if (s[i] == '>')
		return (1);
	if (s[i] == '<')
		return (1);
	if (s[i] == '$')
		return (1);
	if (s[i] == '|')
		return (1);
	return (0);
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
		if (i > 0 && is_determinator(s, i))
			break ;
		i++;
	}
	new_token->val = (char *)malloc(i);
	if (new_token->val == NULL)
		return (NULL);
	ft_strlcpy(new_token->val, s, i);
	return (new_token);
}

t_token	*parse_str(char *s)
{
	if (!check_quotes(s))
		return (NULL);
	
}

void	get_command(t_mini *mini)
{
	char	*s;
	char	*t;

	while (1)
	{
		s = readline("minishell:) ");
		mini->start_tock = parse_str(s);
		while (mini->start_tock)
		{
			t = ft_itoa(mini->start_tock->type);
			write(1, t, ft_strlen(t));
			write(1, " ", 1);
			free(t);
			mini->start_tock = mini->start_tock->next;
		}
		write(1, "\n", 1);
	}
}
