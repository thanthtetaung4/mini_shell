/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_cmd_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:59:45 by taung             #+#    #+#             */
/*   Updated: 2025/03/02 15:59:46 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static char	*handle_path_not_found(char *cmd)
{
	ft_putstr_fd("minishell: PATH not set\n", 2);
	free(cmd);
	return (ft_strdup(""));
}

static void	free_path_resources(char *path_dup, char **dir, char *path_env)
{
	free(path_dup);
	free(dir);
	free(path_env);
}

static char	*try_path_directory(char *dir_path, char *cmd)
{
	char	*full_path;
	int		path_len;

	path_len = ft_strlen(dir_path) + ft_strlen(cmd) + 2;
	full_path = malloc(path_len);
	if (!full_path)
		return (NULL);
	ft_strlcpy(full_path, dir_path, ft_strlen(dir_path) + 1);
	ft_strlcat(full_path, "/", path_len);
	ft_strlcat(full_path, cmd, path_len);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

char	*find_command_path(char *cmd, t_minishell *data)
{
	t_f_cmd_path	f;

	if (cmd[0] == '/' || cmd[0] == '.')
		return (cmd);
	f.path_env = get_env_value(data->env, "PATH");
	if (!f.path_env || ft_strlen(f.path_env) == 0)
		return (handle_path_not_found(cmd));
	f.path_dup = ft_strdup(f.path_env);
	f.dir = ft_split(f.path_dup, ':');
	f.i = 0;
	while (f.dir[f.i])
	{
		f.full_path = try_path_directory(f.dir[f.i], cmd);
		if (f.full_path)
		{
			free(f.path_dup);
			free(cmd);
			return (f.full_path);
		}
		free(f.dir[f.i]);
		f.i++;
	}
	free_path_resources(f.path_dup, f.dir, f.path_env);
	return (ft_strdup(""));
}
