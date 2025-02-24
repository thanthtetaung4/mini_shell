/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 08:12:59 by taung             #+#    #+#             */
/*   Updated: 2025/02/24 23:09:23 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	update_prev_dir(t_minishell *data, char *prev_dir)
{
	export_add_var(data, "OLDPWD", prev_dir);
}

void	update_env_pwd(t_minishell *data)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	export_add_var(data, "PWD", pwd);
	free(pwd);
}

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

int	ft_cd(t_minishell *data)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (data->args_count == 2)
	{
		if (ft_strcmp(data->args[1], "~") == 0)
			return (cd_to_home(data, pwd));
		if (ft_strcmp(data->args[1], "-") == 0)
			return (cd_to_prev(data, pwd));
			if (access(data->args[1], F_OK) == 0)
			{
				if (access(data->args[1], R_OK) == 0)
				{
					if (chdir(data->args[1]) == -1)
					{
						ft_putstr_fd("No such file or directory\n", 2);
						free(pwd);
						return (1);
					}
					else
					{
						update_env_pwd(data);
						update_prev_dir(data, pwd);
					}
				}
			else
			{
				ft_putstr_fd("No permission\n", 2);
				free(pwd);
				return (1);
			}
		}
		else
		{
			ft_putstr_fd(" No such file or directory\n", 2);
			free(pwd);
			return (1);
		}
	}
	else if (data->args_count == 1)
		return (cd_to_home(data, pwd));
	else
	{
		ft_putstr_fd(" too many arguments\n", 2);
		free(pwd);
		return (1);
	}
	free(pwd);
	return (0);
}
