/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshein <lshein@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 06:41:36 by lshein            #+#    #+#             */
/*   Updated: 2025/03/08 06:48:16 by lshein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	execute_without_pipe(t_minishell *data, t_ast_node *node)
{
	char	**args;
	char	**env_strings;
	int		exit_status;

	args = prepare_args_no_pipe(node, data);
	if (!args)
		return (-1);
	env_strings = get_env_strings(data->env);
	exit_status = execve(args[0], args, env_strings);
	if (exit_status == -1)
		handle_command_not_found(args, env_strings, data);
	free_cmd(&env_strings);
	free_2d_string(args);
	free_all(data, 1);
	exit(exit_status);
	return (exit_status);
}

int	execute_with_pipe(t_minishell *data, t_ast_node *node)
{
	char	**args;
	char	**env_strings;
	int		exit_status;

	args = prepare_args_with_pipe(node, data);
	if (!args)
		return (-1);
	env_strings = get_env_strings(data->env);
	exit_status = execve(args[0], args, env_strings);
	if (exit_status == -1)
		handle_command_not_found(args, env_strings, data);
	free_cmd(&env_strings);
	free_2d_string(args);
	exit(exit_status);
	return (exit_status);
}

int	execute_command(t_minishell *data, t_ast_node *node)
{
	int	exit_status;

	if (data->args_count == 0 || ft_strlen(node->command[0]) == 0)
	{
		clean_exit(data, 1, 0);
	}
	if (check_cmd(node->command[0]) == 1)
	{
		exit_status = ft_exec(data, node);
		close_heredoc_fds_p(data);
		free_all(data, 1);
		exit(exit_status);
	}
	else if (data->forking->pipe_count == 0)
	{
		execute_without_pipe(data, node);
	}
	else if (data->forking->pipe_count > 0)
	{
		execute_with_pipe(data, node);
	}
	return (1);
}

void	restore_signals_and_cleanup(t_minishell *data)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	close_heredoc_fds_p(data);
}

int	tree_execution(t_ast_node *lowest_node, t_minishell *data)
{
	int	sig;

	setup_execution_context(data);
	sig = process_heredocs(lowest_node, data);
	if (sig == 1)
	{
		close_heredoc_fds_p(data);
		return (130);
	}
	execute_commands(lowest_node, data);
	wait_for_children(data);
	close_backup_fds(data);
	close_pipe_fds(data);
	restore_signals_and_cleanup(data);
	return (data->status);
}
