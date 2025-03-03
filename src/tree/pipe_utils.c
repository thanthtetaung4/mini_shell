/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshein <lshein@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:59:39 by lshein            #+#    #+#             */
/*   Updated: 2025/03/03 11:39:12 by lshein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	setup_stdin_for_pipe(t_minishell *data, t_ast_node *node)
{
	if (data->forking->completed_piping > 0 && data->empty_prev_node == 0)
	{
		dup2(data->forking->fds[data->forking->i_fd - 1][0], STDIN_FILENO);
	}
	else if (data->forking->completed_piping > 0 && data->empty_prev_node == 1)
	{
		if (data->forking->pipe_count > 1)
		{
			dup2(node->parent->left->right->redirection->heredoc_fd[0],
				STDIN_FILENO);
			close(node->parent->left->right->redirection->heredoc_fd[0]);
		}
		else if (data->forking->pipe_count == 1)
		{
			dup2(node->parent->left->redirection->heredoc_fd[0], STDIN_FILENO);
			close(node->parent->left->redirection->heredoc_fd[0]);
		}
	}
}

void	setup_stdout_for_pipe(t_minishell *data)
{
	if ((data->forking->completed_piping < data->forking->pipe_count))
	{
		dup2(data->forking->fds[data->forking->i_fd][1], STDOUT_FILENO);
	}
}

void	handle_pipe_parent(t_minishell *data, t_ast_node *node, int pid)
{
	close(data->forking->fds[data->forking->i_fd][1]);
	if (!node->command[0]
		|| data->forking->completed_piping == data->forking->pipe_count)
		close(data->forking->fds[data->forking->i_fd][0]);
	data->forking->pids[data->forking->i_pid] = pid;
	data->forking->i_pid++;
	if (data->forking->i_fd > 0)
	{
		close(data->forking->fds[data->forking->i_fd - 1][0]);
	}
}

void	handle_pipe_execution(t_minishell *data, t_ast_node *node)
{
	t_ast_node	*temp_node;

	if (node->type == PIPE)
	{
		temp_node = node->right;
		data->status = execute_pipe_command(data, temp_node);
		data->forking->i_fd++;
		data->forking->completed_piping++;
	}
}

int	handle_pipe_heredoc(t_minishell *data, t_ast_node *node)
{
	int			sig;
	t_ast_node	*temp_node;

	sig = 0;
	if (node->type == PIPE)
	{
		temp_node = node->right;
		if (temp_node->type == COMMAND && temp_node->redirection
			&& temp_node->redirection->heredoc_count > 0)
		{
			sig = heredoc(data, temp_node, 1);
		}
	}
	return (sig);
}
