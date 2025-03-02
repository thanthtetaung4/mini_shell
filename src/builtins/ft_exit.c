/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 07:14:56 by taung             #+#    #+#             */
/*   Updated: 2025/03/02 15:37:38 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	check_valid_args(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (ft_isalpha(arg[i]) && arg[i] != '#')
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_minishell *data)
{
	int	exit_status;

	if (!data->args[1])
	{
		free_all(data, 1);
		ft_putstr_fd("exit\n", 0);
		exit(0);
	}
	else if (data->args_count == 2)
	{
		if (!check_valid_args(data->args[1]))
		{
			ft_putstr_fd(" numeric argument required\n", 2);
			free_all(data, 1);
			exit(2);
		}
		else
		{
			exit_status = ft_atoi(data->args[1]);
			free_all(data, 1);
			exit(exit_status);
		}
	}
	else if (data->args_count > 2)
		ft_putstr_fd(" too many arguments\n", 2);
}
