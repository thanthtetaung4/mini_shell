/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshein <lshein@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:37:58 by lshein            #+#    #+#             */
/*   Updated: 2025/03/06 02:20:45 by lshein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	execute_external_cmd(t_minishell *data, t_ast_node *node)
{
	int	pid;
	int	exit_status;

	exit_status = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
	{
		setup_child_process(data, node);
	}
	else
	{
		waitpid(pid, &exit_status, 0);
		exit_status = handle_child_exit_status(exit_status);
	}
	return (exit_status);
}

int	execute_single_command(t_minishell *data, t_ast_node *node)
{
	int	stdout_fd;
	int	stdin_fd;
	int	exit_status;

	stdout_fd = -1;
	stdin_fd = -1;
	if (!node->command[0])
	{
		if (node->redirection->heredoc_count > 0)
			close(node->redirection->heredoc_fd[0]);
		if (node->redirection->redirection_count > 0)
			open_file_empty_cmd(node);
		return (0);
	}
	if (node->command[0] && check_cmd(node->command[0]))
	{
		save_std_fds(node, &stdout_fd, &stdin_fd);
		exit_status = execute_builtin_with_redirections(data, node, stdout_fd,
				stdin_fd);
	}
	else
		exit_status = execute_external_cmd(data, node);
	if (node->redirection->heredoc_count > 0)
		close(node->redirection->heredoc_fd[0]);
	return (exit_status);
}

void	execute_pipe_child(t_minishell *data, t_ast_node *node)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!node->command[0])
	{
		if (node->redirection->redirection_count > 0)
			open_file_empty_cmd(node);
		handle_empty_command_child(data);
	}
	setup_stdin_for_pipe(data, node);
	setup_stdout_for_pipe(data);
	close_all_pipe_fds(data);
	if (node->redirection->types[0] != -1)
	{
		if (execute_redirection(node, data))
		{
			free_all(data, 1);
			exit(1);
		}
	}
	execute_command(data, node);
	close_heredoc_fds_p(data);
	free_all(data, 1);
}

int	execute_pipe_command(t_minishell *data, t_ast_node *node)
{
	int	pid;
	int	exit_status;

	exit_status = 0;
	data->args_count = ft_count_tds(node->command);
	setup_pipe_fds(data);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
	{
		execute_pipe_child(data, node);
	}
	else
	{
		handle_pipe_parent(data, node, pid);
	}
	update_empty_prev_node(data, node);
	return (exit_status);
}

int	setup_execution_context(t_minishell *data)
{
	init_fds(data);
	init_pids(data);
	data->stdin_backup = -1;
	data->heredoc_backup = -1;
	return (0);
}
