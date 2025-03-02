/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:46:26 by taung             #+#    #+#             */
/*   Updated: 2025/03/02 15:46:46 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	free_redirections(t_ast_node *node)
{
	int	i;

	i = 0;
	free(node->redirection->types);
	while (node->redirection->files[i])
	{
		free(node->redirection->files[i]);
		i++;
	}
	free(node->redirection->files);
	free(node->redirection);
}

void	free_tree_helper(t_ast_node *node)
{
	int	i;

	if (!node)
		return ;
	if (node->left)
		free_tree_helper(node->left);
	if (node->right)
		free_tree_helper(node->right);
	if (node->type == COMMAND && node->command)
	{
		free_redirections(node);
		i = 0;
		while (node->command[i])
		{
			free(node->command[i]);
			i++;
		}
		free(node->command);
	}
	free(node);
}

void	free_tree(t_ast_node *node)
{
	t_ast_node	*root;

	if (!node)
		return ;
	root = node;
	while (root->parent)
		root = root->parent;
	free_tree_helper(root);
}

void	rest_helper(t_minishell *data)
{
	data->forking->i_fd = 0;
	data->forking->i_pid = 0;
	data->forking->i_rfd = 0;
	data->forking->pipe_count = 0;
	data->forking->redirection_count = 0;
	data->forking->completed_piping = 0;
	data->forking->heredoc_count = 0;
}

void	reset_forking_data(t_minishell *data)
{
	int	i;

	i = 0;
	if (data->forking->fds)
	{
		if (data->forking->fds[i])
		{
			while (i < (data->forking->pipe_count + 1))
			{
				free(data->forking->fds[i]);
				i++;
			}
		}
		free(data->forking->fds);
	}
	if (data->forking->pids)
		free(data->forking->pids);
	if (data->forking->redirection_fds)
		free(data->forking->redirection_fds);
	rest_helper(data);
}
