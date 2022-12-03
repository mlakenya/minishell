/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:06:36 by mlakenya          #+#    #+#             */
/*   Updated: 2022/12/03 12:35:14 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_mini	*init_mini(char **env)
{
	t_mini	*mini;

	mini = (t_mini *)malloc(sizeof(t_mini));
	if (!mini)
		return (NULL);
	mini->variables = init_var();
	mini->env = save_env(env);
	increase_shlvl(mini);
	del_var_by_name(mini, "OLDPWD");
	mini->hist_file = get_hist_file_name(mini);
	mini->hd_file = get_hd_file_name(mini);
	mini->history = NULL;
	mini->start_tock = NULL;
	mini->cmd_line = NULL;
	mini->exit_status = 0;
	mini->ret = 0;
	mini->no_exec = 0;
	mini->err_msg = NULL;
	mini->stdin = dup(STDIN);
	mini->stdout = dup(STDOUT);
	reset_fds(mini);
	return (mini);
}
