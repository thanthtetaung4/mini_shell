/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshein <lshein@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:54:29 by lshein            #+#    #+#             */
/*   Updated: 2025/03/03 11:46:09 by lshein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	close_heredoc_fds_c(t_minishell *data)
{
	t_ast_node	*temp_node;

	temp_node = data->tree->lowest_node;
	while (temp_node)
	{
		if (temp_node->type == COMMAND)
		{
			close(temp_node->redirection->heredoc_fd[0]);
			close(temp_node->redirection->heredoc_fd[1]);
		}
		else if (temp_node->type == PIPE)
		{
			close(temp_node->right->redirection->heredoc_fd[0]);
			close(temp_node->right->redirection->heredoc_fd[1]);
		}
		temp_node = temp_node->parent;
	}
}

void	close_heredoc_fds_p(t_minishell *data)
{
	t_ast_node	*temp_node;

	temp_node = data->tree->lowest_node;
	while (temp_node)
	{
		if (temp_node->type == COMMAND)
		{
			if (temp_node->redirection->heredoc_fd[0] != -1)
				close(temp_node->redirection->heredoc_fd[0]);
			if (temp_node->redirection->heredoc_fd[1] != -1)
				close(temp_node->redirection->heredoc_fd[1]);
		}
		else if (temp_node->type == PIPE)
		{
			if (temp_node->right->redirection->heredoc_fd[0] != -1)
				close(temp_node->right->redirection->heredoc_fd[0]);
			if (temp_node->right->redirection->heredoc_fd[1] != -1)
				close(temp_node->right->redirection->heredoc_fd[1]);
		}
		temp_node = temp_node->parent;
	}
}

void	setup_pipe_fds(t_minishell *data)
{
	if (pipe(data->forking->fds[data->forking->i_fd]) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

void	close_all_pipe_fds(t_minishell *data)
{
	int	i;

	i = 0;
	while (i <= data->forking->i_fd)
	{
		close(data->forking->fds[i][0]);
		close(data->forking->fds[i][1]);
		i++;
	}
}
