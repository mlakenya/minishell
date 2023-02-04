/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 04:58:11 by mlakenya          #+#    #+#             */
/*   Updated: 2023/02/04 14:49:58 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	magic_box(char *path, char **args, t_var *env, t_mini *mini)
{
	char	**env_array;
	int		ret;

	ret = SUCCESS;
	g_signals.pid = fork();
	if (g_signals.pid == 0)
	{
		env_array = copy_env(env);
		if (ft_strchr(path, '/') != NULL)
			execve(path, args, env_array);
		ret = error_message(path);
		free_array((void **)args);
		free_array((void **)env_array);
		free_minishell(mini);
		exit(ret);
	}
	else
	{
		waitpid(g_signals.pid, &ret, 0);
		if (ret == 2 && g_signals.sigint)
			sigint_exec();
		if (ret == 131 && g_signals.sigquit)
			sigquit();
	}
	if (g_signals.sigint || g_signals.sigquit)
		return (g_signals.exit_status);
	if (ret == 32256 || ret == 32512)
		ret = ret / 256;
	else
		ret = !!ret;
	return (ret);
}

char	*path_join(const char *s1, const char *s2)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(s1, "/");
	path = ft_strjoin(tmp, s2);
	free(tmp);
	return (path);
}

char	*check_dir(char *bin, char *command)
{
	DIR				*folder;
	struct dirent	*item;
	char			*path;

	path = NULL;
	folder = opendir(bin);
	if (!folder)
		return (NULL);
	item = readdir(folder);
	while (item)
	{
		if (ft_strncmp(item->d_name, command, 1024) == 0)
			path = path_join(bin, item->d_name);
		item = readdir(folder);
	}
	closedir(folder);
	return (path);
}

int	exec_bin(char **args, t_var *env, t_mini *mini)
{
	int		i;
	char	**bin;
	char	*path;
	int		ret;

	i = 0;
	ret = UNKNOWN_COMMAND;
	while (env && ft_strncmp(env->name, "PATH", 4) != 0)
		env = env->next;
	if (env == NULL || env->next == NULL)
		return (magic_box(args[0], args, mini->env, mini));
	bin = ft_split(env->value, ':');
	if (!args[0] && !bin[0])
		return (ERROR);
	i = 1;
	path = check_dir(bin[0] + 5, args[0]);
	while (args[0] && bin[i] && path == NULL)
		path = check_dir(bin[i++], args[0]);
	free_array((void **)bin);
	if (path != NULL)
		ret = magic_box(path, args, mini->env, mini);
	else
		ret = magic_box(args[0], args, mini->env, mini);
	free(path);
	return (ret);
}
