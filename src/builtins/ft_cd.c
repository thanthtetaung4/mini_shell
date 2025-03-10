/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshein <lshein@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 08:12:59 by taung             #+#    #+#             */
/*   Updated: 2025/03/04 14:24:49 by lshein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	cd_to_home(t_minishell *data, char *pwd)
{
	char	*home_dir;
	int		status;

	home_dir = get_env_value(data->env, "HOME");
	if (ft_strlen(home_dir) == 0)
	{
		ft_putstr_fd("HOME is not set\n", 2);
		free(home_dir);
		free(pwd);
		return (1);
	}
	status = chdir(home_dir);
	if (status != -1)
	{
		update_prev_dir(data, pwd);
		update_env_pwd(data);
	}
	free(home_dir);
	free(pwd);
	return (status);
}

int	cd_to_prev(t_minishell *data, char *pwd)
{
	int		status;
	char	*tmp;

	status = 0;
	tmp = get_env_value(data->env, "OLDPWD");
	if (ft_strlen(tmp) == 0)
	{
		ft_putstr_fd("OLDPWD is not set\n", 2);
		free(tmp);
		free(pwd);
		return (1);
	}
	status = chdir(tmp);
	if (status != -1)
	{
		update_prev_dir(data, pwd);
		update_env_pwd(data);
	}
	printf("%s\n", tmp);
	free(tmp);
	free(pwd);
	return (status);
}

int	change_directory(t_minishell *data, char *pwd, const char *path)
{
	if (access(path, F_OK) == 0)
	{
		if (access(path, R_OK) == 0)
		{
			if (chdir(path) == -1)
				return (handle_cd_error(pwd, "No such file or directory\n"));
			else
			{
				update_prev_dir(data, pwd);
				update_env_pwd(data);
			}
		}
		else
			return (handle_cd_error(pwd, "No permission\n"));
	}
	else
		return (handle_cd_error(pwd, "No such file or directory\n"));
	free(pwd);
	return (0);
}

int	handle_cd_args(t_minishell *data, char *pwd, t_ast_node *node)
{
	if (ft_strcmp(node->command[1], "~") == 0)
		return (cd_to_home(data, pwd));
	if (ft_strcmp(node->command[1], "-") == 0)
		return (cd_to_prev(data, pwd));
	return (change_directory(data, pwd, node->command[1]));
}

int	ft_cd(t_minishell *data, t_ast_node *node)
{
	char	*pwd;
	int		cmd_count;

	cmd_count = ft_count_tds(node->command);
	pwd = getcwd(NULL, 0);
	if (cmd_count == 2)
		return (handle_cd_args(data, pwd, node));
	else if (cmd_count == 1)
		return (cd_to_home(data, pwd));
	else
		return (handle_cd_error(pwd, "too many arguments\n"));
	free(pwd);
	return (0);
}
