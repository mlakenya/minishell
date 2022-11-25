/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 08:18:19 by mlakenya          #+#    #+#             */
/*   Updated: 2022/11/21 11:32:20 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void		print_error(char **args)
{
	ft_putstr_fd("cd: ", 2);
	if (args[2])
		ft_putstr_fd("string not in pwd: ", 2);
	else
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(args[1], 2);
}

static int		update_oldpwd(t_mini *mini)
{
	char	cwd[1024];
	char	*oldpwd;

	if (getcwd(cwd, 1024) == NULL)
		return (ERROR);
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	if (!oldpwd)
		return (ERROR);
	is_variable(oldpwd, mini);
	free(oldpwd);
	return (SUCCESS);
}

static int		go_to_path(int option, t_mini *mini)
{
	int		ret;
	char	*env_path;
    t_var   *var;

	env_path = NULL;
	if (option == 0)
	{
		update_oldpwd(mini);
		var = find_variable("HOME", mini, 10000000);
		if (!var)
            ft_putendl_fd("minishell : cd: HOME not set", STDERR);
        if (!var)
            return (ERROR);
        env_path = var->value;
	}
	else if (option == 1)
	{
		var = find_variable("OLDPWD", mini, 10000000);
		if (!var)
			ft_putendl_fd("minishell : cd: OLDPWD not set", STDERR);
		if (!var)
			return (ERROR);
		update_oldpwd(mini);
        env_path = var->value;
	}
	ret = chdir(env_path);
	free(env_path);
	return (ret);
}

int	ft_cd(char **args, t_mini *mini)
{
	int	cd_ret;

	if (!args[1])
		return (go_to_path(0, mini));
	if (ft_strncmp(args[1], "-", 1) == 0)
		cd_ret = go_to_path(1, mini);
	else
	{
		update_oldpwd(mini);
		cd_ret = chdir(args[1]);
		if (cd_ret < 0)
			cd_ret *= -1;
		if (cd_ret != 0)
			print_error(args);
	}
	return (cd_ret);
}
