/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshein <lshein@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 06:41:36 by lshein            #+#    #+#             */
/*   Updated: 2025/03/03 11:05:22 by lshein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	execute_command(t_minishell *data, t_ast_node *node)
{
	int			i;
	char		**args;
	char		**env_strings;
	struct stat	path_stat;
	int			exit_status;

	if (data->args_count == 0 || ft_strlen(node->command[0]) == 0)
		return (0);
	if (check_cmd(node->command[0]) == 1)
	{
		exit_status = ft_exec(data, node);
		free_all(data, 1);
		exit(exit_status);
	}
	else if (data->forking->pipe_count == 0)
	{
		args = malloc(sizeof(char *) * (data->args_count + 1));
		if (node->command[0][0] == '.' && node->command[0][1] == '/')
		{
			if (stat(node->command[0], &path_stat) == 0)
			{
				if (S_ISDIR(path_stat.st_mode))
				{
					ft_putstr_fd(" Is a directory\n", 2);
					free(args);
					free_all(data, 1);
					exit(126);
				}
			}
			if (access(node->command[0], F_OK) != 0)
			{
				ft_putstr_fd(" No such file or directory\n", 2);
				free(args);
				free_all(data, 1);
				exit(127);
			}
			if (access(node->command[0], X_OK) != 0)
			{
				ft_putstr_fd(" Permission denied\n", 2);
				free(args);
				free_all(data, 1);
				exit(126);
			}
		}
		if (node->command[0][0] == '/')
		{
			if (stat(node->command[0], &path_stat) == 0)
			{
				if (S_ISDIR(path_stat.st_mode))
				{
					ft_putstr_fd(" Is a directory\n", 2);
					free(args);
					free_all(data, 1);
					exit(126);
				}
			}
			if (access(node->command[0], F_OK) != 0)
			{
				ft_putstr_fd(" No such file or directory\n", 2);
				free(args);
				free_all(data, 1);
				exit(127);
			}
		}
		args[0] = ft_strdup(node->command[0]);
		if ((node->command[0][0] != '.' && node->command[0][1] != '/')
			&& ft_strncmp(node->command[0], "/bin/", 5) != 0)
		{
			args[0] = find_command_path(args[0], data);
		}
		i = 1;
		while (node->command[i])
		{
			args[i] = ft_strdup(node->command[i]);
			i++;
		}
		args[i] = NULL;
		env_strings = get_env_strings(data->env);
		exit_status = execve(args[0], args, env_strings);
		if (exit_status == -1)
		{
			ft_putstr_fd(" command not found\n", 2);
			free_2d_string(args);
			free_cmd(&env_strings);
			free_all(data, 1);
			exit(127);
		}
		free_cmd(&env_strings);
		free_2d_string(args);
		free_all(data, 1);
		exit(exit_status);
	}
	else if (data->forking->pipe_count > 0)
	{
		args = malloc(sizeof(char *) * (data->args_count + 1));
		if (node->command[0][0] == '.' && node->command[0][1] == '/')
		{
			if (stat(node->command[0], &path_stat) == 0)
			{
				if (S_ISDIR(path_stat.st_mode))
				{
					ft_putstr_fd(" Is a directory\n", 2);
					free(args);
					free_all(data, 1);
					exit(126);
				}
			}
			if (access(node->command[0], F_OK) != 0)
			{
				ft_putstr_fd(" No such file or directory\n", 2);
				free(args);
				free_all(data, 1);
				exit(127);
			}
			if (access(node->command[0], X_OK) != 0)
			{
				ft_putstr_fd(" Permission denied\n", 2);
				free(args);
				free_all(data, 1);
				exit(126);
			}
		}
		if (node->command[0][0] == '/')
		{
			if (stat(node->command[0], &path_stat) == 0)
			{
				if (S_ISDIR(path_stat.st_mode))
				{
					ft_putstr_fd(" Is a directory\n", 2);
					free(args);
					free_all(data, 1);
					exit(126);
				}
			}
			if (access(node->command[0], F_OK) != 0)
			{
				ft_putstr_fd(" No such file or directory\n", 2);
				free(args);
				free_all(data, 1);
				exit(127);
			}
		}
		args[0] = ft_strdup(node->command[0]);
		if ((node->command[0][0] != '.' && node->command[0][1] != '/')
			&& ft_strncmp(node->command[0], "/bin/", 5) != 0)
		{
			args[0] = find_command_path(node->command[0], data);
		}
		i = 1;
		while (i < data->args_count)
		{
			args[i] = ft_strdup(node->command[i]);
			i++;
		}
		args[i] = NULL;
		env_strings = get_env_strings(data->env);
		exit_status = execve(args[0], args, env_strings);
		if (exit_status == -1)
		{
			ft_putstr_fd(" command not found\n", 2);
			free_2d_string(args);
			free_cmd(&env_strings);
			free_all(data, 1);
			exit(127);
		}
		free_cmd(&env_strings);
		free_2d_string(args);
		exit(exit_status);
	}
	return (1);
}

static void	restore_signals_and_cleanup(t_minishell *data)
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
		return (1);
	}
	execute_commands(lowest_node, data);
	wait_for_children(data);
	handle_signal_status(data);
	close_backup_fds(data);
	close_pipe_fds(data);
	restore_signals_and_cleanup(data);
	return (data->status);
}
