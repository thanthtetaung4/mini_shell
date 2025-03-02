/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 08:12:59 by taung             #+#    #+#             */
/*   Updated: 2025/03/02 15:41:52 by taung            ###   ########.fr       */
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

	tmp = get_env_value(data->env, "OLDPWD");
	if (ft_strlen(tmp) == 0)
	{
		ft_putstr_fd("OLDPWD is not set\n", 2);
		return (status);
	}
	status = chdir(tmp);
	if (status != -1)
	{
		update_env_pwd(data);
		update_prev_dir(data, pwd);
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
				update_env_pwd(data);
				update_prev_dir(data, pwd);
			}
		}
		else
			return (handle_cd_error(pwd, "No permission\n"));
	}
	else
		return (handle_cd_error(pwd, "No such file or directory\n"));
	return (0);
}

int	handle_cd_args(t_minishell *data, char *pwd)
{
	if (ft_strcmp(data->args[1], "~") == 0)
		return (cd_to_home(data, pwd));
	if (ft_strcmp(data->args[1], "-") == 0)
		return (cd_to_prev(data, pwd));
	return (change_directory(data, pwd, data->args[1]));
}

int	ft_cd(t_minishell *data)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (data->args_count == 2)
		return (handle_cd_args(data, pwd));
	else if (data->args_count == 1)
		return (cd_to_home(data, pwd));
	else
		return (handle_cd_error(pwd, "too many arguments\n"));
	free(pwd);
	return (0);
}
