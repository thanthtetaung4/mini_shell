/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshein <lshein@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:05:08 by lshein            #+#    #+#             */
/*   Updated: 2025/03/03 11:38:36 by lshein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	process_heredocs(t_ast_node *lowest_node, t_minishell *data)
{
	t_ast_node	*node;
	int			sig;

	node = lowest_node;
	sig = 0;
	while (node && !sig)
	{
		sig = handle_command_heredoc(data, node);
		if (sig)
			return (sig);
		sig = handle_pipe_heredoc(data, node);
		if (sig)
			return (sig);
		if (node->parent)
			node = node->parent;
		else
			break ;
	}
	return (sig);
}

void	handle_command_execution(t_minishell *data, t_ast_node *node)
{
	if (node->parent && node->parent->type == PIPE)
	{
		data->status = execute_pipe_command(data, node);
		data->forking->i_fd++;
		data->forking->completed_piping++;
	}
	else if (!node->parent)
	{
		data->status = execute_single_command(data, node);
	}
}

void	execute_commands(t_ast_node *lowest_node, t_minishell *data)
{
	t_ast_node	*node;

	node = lowest_node;
	while (node)
	{
		if (node->type == COMMAND)
		{
			handle_command_execution(data, node);
		}
		else
		{
			handle_pipe_execution(data, node);
		}
		if (node->parent)
			node = node->parent;
		else
			break ;
	}
}

void	wait_for_children(t_minishell *data)
{
	int	i;

	i = 0;
	while (i < data->forking->completed_piping)
	{
		waitpid(data->forking->pids[i], &data->status, 0);
		i++;
	}
}

void	handle_signal_status(t_minishell *data)
{
	int	sig;

	if (data->forking->pipe_count > 0)
	{
		if (WIFSIGNALED(data->status))
		{
			sig = WTERMSIG(data->status);
			if (sig == SIGINT)
			{
				write(1, "\n", 1);
				data->status = 0;
			}
		}
		else if (WIFEXITED(data->status))
		{
			data->status = WEXITSTATUS(data->status);
		}
	}
}
