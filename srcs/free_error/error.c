/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 08:24:59 by mlakenya          #+#    #+#             */
/*   Updated: 2022/12/13 18:10:51 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_error_no_exit(char *name, char *flag, char *err)
{
	if (name)
		ft_putstr2_fd(name, ": ", STDERR_FILENO);
	if (flag)
		ft_putstr2_fd(flag, ": ", STDERR_FILENO);
	if (err)
		ft_putstr2_fd(err, "\n", STDERR_FILENO);
}

void	print_error_exit(t_mini *minishell, char *name, char *flag, char *err)
{
	int	exit_status;

	exit_status = minishell->ret;
	print_error_no_exit(name, flag, err);
	free_tocken_add_history(minishell);
	append_history_file(minishell);
	free_minishell(minishell);
	exit(exit_status);
}

void	init_error(t_mini *minishell)
{
	if (!minishell)
		print_error_exit(minishell, "Environment init: ", NULL,
			strerror(errno));
	else
	{
		if (!minishell->env)
			print_error_exit(minishell, "Environment init: ",
				"environment saving error: ", strerror(errno));
		if (!minishell->hist_file)
			print_error_exit(minishell, "Environment init: ",
				"history file error: ", strerror(errno));
	}
}

char	*error_message2(char *path, int fd, DIR *folder)
{
	if (ft_strchr(path, '/') == NULL)
	{
		return (": command not found");
	}
	else if (fd == -1 && folder == NULL)
	{
		return (": No such file or directory");
	}
	else if (fd == -1 && folder != NULL)
	{
		return (": is a directory");
	}
	else if (fd != -1 && folder == NULL)
	{
		return (": Permission denied");
	}
	return (NULL);
}

int	error_message(char *path)
{
	DIR		*folder;
	char	*tmp;
	char	*err;
	int		fd;
	int		ret;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	err = ft_strdup("minishell: ");
	tmp = err;
	err = ft_strjoin(err, path);
	free(tmp);
	tmp = err;
	err = ft_strjoin(err, error_message2(path, fd, folder));
	free(tmp);
	if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
		ret = UNKNOWN_COMMAND;
	else
		ret = IS_DIRECTORY;
	if (folder)
		closedir(folder);
	ft_putendl_fd(err, STDERR);
	free(err);
	ft_close(fd);
	return (ret);
}
