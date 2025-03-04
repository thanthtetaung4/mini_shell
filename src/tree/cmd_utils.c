/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshein <lshein@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:36:33 by lshein            #+#    #+#             */
/*   Updated: 2025/03/04 14:37:31 by lshein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	check_directory_permissions(char *cmd_path, char **args,
		t_minishell *data)
{
	struct stat	path_stat;

	if (stat(cmd_path, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			ft_putstr_fd(" Is a directory\n", 2);
			free(args);
			free_all(data, 1);
			exit(126);
		}
	}
}

void	check_file_exists(char *cmd_path, char **args, t_minishell *data)
{
	if (access(cmd_path, F_OK) != 0)
	{
		ft_putstr_fd(" No such file or directory\n", 2);
		free(args);
		free_all(data, 1);
		exit(127);
	}
}

void	check_execute_permission(char *cmd_path, char **args, t_minishell *data)
{
	if (cmd_path[0] == '.' && cmd_path[1] == '/' && access(cmd_path, X_OK) != 0)
	{
		ft_putstr_fd(" Permission denied\n", 2);
		free(args);
		free_all(data, 1);
		exit(126);
	}
}

void	validate_command_path(char *cmd_path, char **args, t_minishell *data)
{
	check_directory_permissions(cmd_path, args, data);
	check_file_exists(cmd_path, args, data);
	if (cmd_path[0] == '.' && cmd_path[1] == '/')
		check_execute_permission(cmd_path, args, data);
}

void	handle_command_not_found(char **args, char **env_strings,
		t_minishell *data)
{
	ft_putstr_fd(" command not found\n", 2);
	free_2d_string(args);
	free_cmd(&env_strings);
	free_all(data, 1);
	exit(127);
}
