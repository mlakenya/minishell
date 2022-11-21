/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakenya <mlakenya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 15:10:58 by mlakenya          #+#    #+#             */
/*   Updated: 2022/11/19 22:39:30 by mlakenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_hd_file_name(t_mini *minishell)
{
	char	*buff_1;
	char	*buff_2;

	buff_1 = NULL;
	buff_1 = getcwd(buff_1, 1024);
	if (!buff_1)
		print_error_exit(minishell, NULL, NULL, strerror(errno));
	buff_2 = ft_strjoin(buff_1, "/.m_heredoc");
	free(buff_1);
	if (!buff_2)
		print_error_exit(minishell, NULL, NULL, strerror(errno));
	return (buff_2);
}
