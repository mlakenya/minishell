/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:06:36 by mlakenya          #+#    #+#             */
/*   Updated: 2022/11/20 23:13:35 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mini	*init_mini(char **env)
{
	t_mini	*mini;

	mini = (t_mini *)malloc(sizeof(t_mini));
	if (!mini)
		return (NULL);
	mini->env_str = env;
	mini->env = save_env(env);
	increase_shlvl(mini);
	remove_oldpwd_value(mini->env);
	mini->env_str = copy_env(mini->env);
	mini->path_array = save_path(find_list(mini->env, "PATH"));
	mini->hist_file = get_hist_file_name(mini);
	mini->hd_file = get_hd_file_name(mini);
	mini->start_tock = NULL;
	mini->cmd_line = NULL;
	mini->exit_status = 0;
	mini->variables = init_var();
	return (mini);
}
