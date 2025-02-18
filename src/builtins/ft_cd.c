/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 08:12:59 by taung             #+#    #+#             */
/*   Updated: 2025/02/17 07:05:12 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	update_prev_dir(t_minishell *data)
{
	char	*prev_dir;

	prev_dir = getcwd(NULL, 0);
	update_export_var(data, prev_dir, find_var(&(data->export), "OLDPWD"));
	ft_update_env(&data->env, ft_envnew("OLDPWD", prev_dir));
}

int	cd_to_home(t_minishell *data)
{
	char	*home_dir;
	int		status;

	update_prev_dir(data);
	home_dir = get_env_value(data->env, "HOME");
	status = chdir(home_dir);
	free(home_dir);
	return (status);
}

int	cd_to_prev(t_minishell *data)
{
	int		status;
	char	*tmp;

	tmp = get_env_value(data->env, "OLDPWD");
	update_prev_dir(data);
	status = chdir(tmp);
	printf("%s\n", tmp);
	free(tmp);
	return (status);
}

int	ft_cd(t_minishell *data)
{
	if (data->args_count == 2)
	{
		if (ft_strcmp(data->args[1], "~") == 0)
			return (cd_to_home(data));
		if (ft_strcmp(data->args[1], "-") == 0)
			return (cd_to_prev(data));
		update_prev_dir(data);
		if (chdir(data->args[1]) == 1)
		{
			printf("No such file or directory\n");
			return (1);
		}
	}
	else if (data->args_count == 1)
		return (cd_to_home(data));
	else
	{
		printf("Too many arguements\n");
		return (1);
	}
	return (0);
}
