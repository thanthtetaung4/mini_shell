/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshein <lshein@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:44:44 by lshein            #+#    #+#             */
/*   Updated: 2025/03/03 11:37:56 by lshein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	handle_heredoc_if_needed(t_ast_node *node, int i)
{
	int	result;

	if (node->redirection->types[i] == HEREDOC)
	{
		result = handle_heredoc_redirection(node);
		if (!node->redirection->types[i + 1])
			return (-1);
	}
	return (0);
}

int	process_file_redirection(t_ast_node *node, t_minishell *data, int i)
{
	int	result;

	if (access(node->redirection->files[i], F_OK) == 0)
		result = handle_existing_file_redirection(node, data, i);
	else
		result = handle_new_file_redirection(node, data, i);
	return (result);
}

int	execute_redirection(t_ast_node *node, t_minishell *data)
{
	int	i;
	int	result;

	i = 0;
	while (node->redirection->types[i] != -1
		&& node->redirection->files[i] != NULL)
	{
		if (handle_heredoc_if_needed(node, i) == -1)
			break ;
		result = process_file_redirection(node, data, i);
		if (result != 0)
			return (result);
		i++;
	}
	return (0);
}

int	execute_builtin_with_redirections(t_minishell *data, t_ast_node *node,
		int stdout_fd, int stdin_fd)
{
	int	exit_status;

	exit_status = 0;
	if (node->redirection->types[0] != -1)
	{
		if (execute_redirection(node, data))
		{
			restore_std_fds(stdout_fd, stdin_fd);
			return (1);
		}
	}
	exit_status = ft_exec(data, node);
	restore_std_fds(stdout_fd, stdin_fd);
	return (exit_status);
}
