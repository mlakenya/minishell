/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 15:06:31 by mlakenya          #+#    #+#             */
/*   Updated: 2022/11/20 22:25:42 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_hist_file_name(t_mini *minishell)
{
	char	*buff_1;
	char	*buff_2;
	t_var	*shlvl;

	shlvl = find_list(minishell->env, "SHLVL");
	if (!shlvl)
		print_error_exit(minishell, "Environment init: ",
			NULL, "shell level error");
	buff_1 = NULL;
	buff_1 = getcwd(buff_1, 1024);
	if (!buff_1)
		print_error_exit(minishell, NULL, NULL, strerror(errno));
	buff_2 = ft_strjoin(buff_1, "/.m_shell_hist_shlvl_");
	free(buff_1);
	if (!buff_2)
		print_error_exit(minishell, NULL, NULL, strerror(errno));
	buff_1 = ft_strjoin(buff_2, shlvl->value);
	free(buff_2);
	if (!buff_1)
		print_error_exit(minishell, NULL, NULL, strerror(errno));
	return (buff_1);
}

static void	add_history_list_end(t_mini *minishell, t_hist *node)
{
	if (minishell->history->prev)
	{
		minishell->history->prev->next = node;
		node->prev = minishell->history->prev;
		minishell->history->prev = node;
	}
	else
	{
		minishell->history->next = node;
		minishell->history->prev = node;
		node->prev = minishell->history;
	}
}

void	add_history_list(t_mini *minishell, char *line)
{
	t_hist	*node;

	node = (t_hist *)malloc(sizeof(t_hist));
	if (!node)
		print_error_no_exit(NULL, NULL, strerror(errno));
	else
	{
		node->line = line;
		node->next = NULL;
		node->prev = NULL;
		if (!minishell->history)
			minishell->history = node;
		else if (minishell->history)
			add_history_list_end(minishell, node);
	}
}

void	read_history_file(t_mini *minishell)
{
	int		fd;
	char	*line;

	fd = open(minishell->hist_file, O_RDONLY | O_CREAT, 0644);
	if (fd == -1)
		print_error_no_exit(NULL, NULL, strerror(errno));
	else
	{
		line = get_next_line(fd);
		while (line)
		{
			remove_end_line_sign(line);
			add_history(line);
			free(line);
			line = get_next_line(fd);
		}
		if (close(fd) == -1)
			print_error_no_exit(NULL, NULL, strerror(errno));
	}
}

void	append_history_file(t_mini *minishell)
{
	t_hist	*node;
	int		fd;

	if (minishell)
	{
		node = minishell->history;
		fd = open(minishell->hist_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			print_error_no_exit(NULL, NULL, strerror(errno));
		else
		{
			while (node)
			{
				if (node->line)
				{
					ft_putstr_fd(node->line, fd);
					ft_putstr_fd("\n", fd);
				}
				node = node->next;
			}
			if (close(fd) == -1)
				print_error_no_exit(NULL, NULL, strerror(errno));
		}
	}
}
