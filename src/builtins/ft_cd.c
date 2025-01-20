/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 08:12:59 by taung             #+#    #+#             */
/*   Updated: 2025/01/19 05:34:24 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	cd_to_home(t_minishell *data)
{
	char	*home_dir;
	int		status;

	home_dir = get_env_value(data->env, "HOME");
	status = chdir(home_dir);
	free(home_dir);
	return (status);
}
int	ft_cd(t_minishell *data)
{
	if (data->args_count == 2)
	{
		if (ft_strcmp(data->args[1], "~") == 0)
			return (cd_to_home(data));
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
