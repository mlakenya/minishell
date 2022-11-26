/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 22:30:00 by mlakenya          #+#    #+#             */
/*   Updated: 2022/11/26 06:26:46 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_errors(t_token *token)
{
	char	*s;

	if (!token->next)
	{
		ft_putendl_fd("zsh: parse error near \'\n\'", STDERR);
		return (1);
	}
	if (token->next->type != CMD)
	{
		s = ft_strjoin("zsh: parse error near ", token->next->val);
		ft_putendl_fd(s, STDERR);
		free(s);
		return (1);
	}
	return (0);
}

int	heredoc(t_token *token, t_mini *mini)
{
	int		fd;
	char	*new_s;

	if (check_errors(token))
		return (0);
	fd = open(mini->hd_file, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	while (1)
	{
		new_s = readline(">");
		if (!new_s || !new_s[0])
			continue ;
		if (ft_strncmp(new_s, token->next->val, 1024) == 0)
		{
			free(new_s);
			break ;
		}
		ft_putendl_fd(new_s, fd);
		free(new_s);
	}
	ft_close(fd);
	return (1);
}

int	handle_heredocs(t_mini *mini)
{
	t_token	*token;

	token = mini->start_tock;
	while (token && !mini->exit_status)
	{
		if (token->type == HEREDOC)
		{
			return (heredoc(token, mini));
		}
		token = token->next;
	}
	return (1);
}
