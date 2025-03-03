/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshein <lshein@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:57:25 by lshein            #+#    #+#             */
/*   Updated: 2025/03/03 11:37:08 by lshein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	close_backup_fds(t_minishell *data)
{
	if (data->heredoc_backup != -1)
		close(data->heredoc_backup);
	if (data->stdin_backup != -1)
		close(data->stdin_backup);
}

void	close_pipe_fds(t_minishell *data)
{
	int	i;

	i = 0;
	while (i < data->forking->i_fd)
	{
		if (data->forking->fds[i])
		{
			close(data->forking->fds[i][0]);
			close(data->forking->fds[i][1]);
		}
		i++;
	}
}
