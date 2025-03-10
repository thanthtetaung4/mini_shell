/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshein <lshein@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 06:38:24 by lshein            #+#    #+#             */
/*   Updated: 2025/03/04 14:40:48 by lshein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	init_forking_data(t_minishell *data)
{
	data->forking = malloc(sizeof(t_forking));
	data->forking->pids = NULL;
	data->forking->pipe_count = 0;
	data->forking->fds = NULL;
	data->forking->redirection_count = 0;
	data->forking->redirection_fds = NULL;
	data->forking->heredoc_count = 0;
	data->forking->i_fd = 0;
	data->forking->i_pid = 0;
	data->forking->i_rfd = 0;
	data->forking->completed_piping = 0;
}

int	init_pids(t_minishell *data)
{
	int	num_of_pids;

	num_of_pids = 0;
	if (data->forking->pipe_count > 0)
		num_of_pids = data->forking->pipe_count + 1;
	data->forking->pids = malloc(sizeof(int) * (num_of_pids));
	if (!data->forking->pids)
		return (-1);
	return (num_of_pids);
}

void	init_fds_helper(t_minishell *data)
{
	int	i;

	i = 0;
	while (i < data->forking->redirection_count)
	{
		data->forking->redirection_fds[i] = -1;
		i++;
	}
}

void	init_fds(t_minishell *data)
{
	int	fds_count;
	int	i;

	i = 0;
	if (data->forking->pipe_count > 0)
	{
		fds_count = data->forking->pipe_count + 1;
		data->forking->fds = malloc(sizeof(int *) * fds_count);
		if (!data->forking->fds)
			return ;
		while (i < fds_count)
		{
			data->forking->fds[i] = malloc(sizeof(int) * 2);
			i++;
		}
	}
	else
		data->forking->fds = NULL;
	if (data->forking->redirection_count > 0)
	{
		data->forking->redirection_fds = malloc((sizeof(int)
					* data->forking->redirection_count));
	}
	else
		data->forking->redirection_fds = NULL;
}

int	init_data(t_minishell *data, char **envp)
{
	data->env = NULL;
	data->input = NULL;
	data->export = NULL;
	data->env = (load_env(envp));
	data->args = NULL;
	data->status = 0;
	data->tree = malloc(sizeof(t_tree));
	data->tree->lowest_node = NULL;
	data->empty_prev_node = 0;
	init_forking_data(data);
	load_export_vars(data);
	return (1);
}
