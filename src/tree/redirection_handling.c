/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 06:29:52 by lshein            #+#    #+#             */
/*   Updated: 2025/03/04 20:48:23 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	handle_output_redirection(t_ast_node *node, t_minishell *data, int i)
{
	int	file_fd;
	if (node->redirection->types[i] == OUTPUT)
		file_fd = open(node->redirection->files[i],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		file_fd = open(node->redirection->files[i],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (file_fd == -1)
	{
		ft_putstr_fd("cannot open output file\n", 2);
		return (EXIT_FAILURE);
	}
	data->forking->redirection_fds[data->forking->i_rfd] = file_fd;
	data->forking->i_rfd++;
	dup2(file_fd, STDOUT_FILENO);
	close(file_fd);
	return (0);
}

int	handle_input_redirection(t_ast_node *node, t_minishell *data, int i)
{
	int	file_fd;

	file_fd = open(node->redirection->files[i], O_RDONLY);
	if (file_fd == -1)
	{
		perror("Error opening input file");
		return (EXIT_FAILURE);
	}
	data->forking->redirection_fds[data->forking->i_rfd] = file_fd;
	data->forking->i_rfd++;
	dup2(file_fd, STDIN_FILENO);
	close(file_fd);
	return (0);
}

int	handle_heredoc_redirection(t_ast_node *node)
{
	dup2(node->redirection->heredoc_fd[0], STDIN_FILENO);
	close(node->redirection->heredoc_fd[0]);
	return (0);
}

int	handle_existing_file_redirection(t_ast_node *node, t_minishell *data, int i)
{
	if (node->redirection->types[i] == OUTPUT
		|| node->redirection->types[i] == APPEND)
	{
		if (access(node->redirection->files[i], W_OK) == 0
			&& access(node->redirection->files[i], R_OK) == 0)
			return (handle_output_redirection(node, data, i));
		else
		{
			ft_putstr_fd(node->redirection->files[i], 2);
			ft_putstr_fd(": Permission denied\n", 2);
			return (EXIT_FAILURE);
		}
	}
	else if (node->redirection->types[i] == INPUT)
	{
		if (access(node->redirection->files[i], R_OK) == 0)
			return (handle_input_redirection(node, data, i));
		else
		{
			ft_putstr_fd(node->redirection->files[i], 2);
			ft_putstr_fd(": Permission denied\n", 2);
			return (EXIT_FAILURE);
		}
	}
	return (0);
}

int	handle_new_file_redirection(t_ast_node *node, t_minishell *data, int i)
{
	if (node->redirection->types[i] == OUTPUT
		|| node->redirection->types[i] == APPEND)
	{
		return (handle_output_redirection(node, data, i));
	}
	else if (node->redirection->types[i] == INPUT)
	{
		return (handle_input_redirection(node, data, i));
	}
	return (0);
}
