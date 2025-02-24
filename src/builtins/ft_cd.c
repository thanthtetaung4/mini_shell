/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 08:12:59 by taung             #+#    #+#             */
/*   Updated: 2025/02/23 02:08:00 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	update_prev_dir(t_minishell *data, char *prev_dir)
{
	char	*oldpwd;

	// oldpwd = get_env_value(data->env, "OLDPWD");
	// if (ft_strlen(oldpwd) == 0)
	// {
	// 	export_add_var(data, "OLDPWD", prev_dir);
	// 	free(prev_dir);
	// 	free(oldpwd);
	// 	return;
	// }
	// free(oldpwd);
	// update_export_var(data, prev_dir, find_var(&(data->export), "OLDPWD"));
	// ft_update_env(&data->env, ft_envnew("OLDPWD", prev_dir));
	export_add_var(data, "OLDPWD", prev_dir);
	// free(prev_dir);

}

void	update_env_pwd(t_minishell *data)
{
	char	*pwd;
	char	*pwd_env;

	pwd = getcwd(NULL, 0);
	export_add_var(data, "PWD", pwd);
	// pwd_env = get_env_value(data->env, "PWD");
	// if (ft_strlen(pwd_env) == 0)
	// {
	// 	export_add_var(data, "PWD", pwd);
	// 	free(pwd_env);
	// 	free(pwd);
	// 	return;
	// }
	// update_export_var(data, pwd, find_var(&(data->export), "PWD"));
	// ft_update_env(&data->env, ft_envnew("PWD", pwd));
	free(pwd);
	// free(pwd_env);
}

int	cd_to_home(t_minishell *data, char *pwd)
{
	char	*home_dir;
	int		status;

	update_prev_dir(data, pwd);
	home_dir = get_env_value(data->env, "HOME");
	status = chdir(home_dir);
	free(home_dir);
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
	update_prev_dir(data, pwd);
	status = chdir(tmp);
	printf("%s\n", tmp);
	free(tmp);
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
						return (1);
					}
					else
					{
						update_prev_dir(data, pwd);
						update_env_pwd(data);
					}
				}
			else
			{
				ft_putstr_fd("No permission\n", 2);
				return (1);
			}
		}
		else
		{
			ft_putstr_fd(" No such file or directory\n", 2);
			return (1);
		}
	}
	else if (data->args_count == 1)
		return (cd_to_home(data, pwd));
	else
	{
		ft_putstr_fd(" too many arguments\n", 2);
		return (1);
	}
	return (0);
}
