/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 07:14:56 by taung             #+#    #+#             */
/*   Updated: 2025/01/18 08:01:12 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int		check_valid_args(char *arg)
{
	int	i;

	i = 0;
	while(arg[i])
	{
		if (ft_isalpha(arg[i]) && arg[i] != '#')
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_minishell *data)
{
	if (!data->args[1])
	{
		free_all(data);
		ft_putstr_fd("exit\n",0);
		exit(0);
	}
	else if (data->args[1])
	{
		if (!check_valid_args(data->args[1]))
		{
			ft_putstr_fd("exit: ", 1);
			ft_putstr_fd(data->args[1], 1);
			ft_putstr_fd(": numeric argument require\n", 1);
			free_all(data);
			exit(1);
		}
		else
		{
			free_all(data);
			exit(1);
		}
	}
	else if (data->args[2])
	{
		ft_putstr_fd("exit: too many arguments\n",0);
	}
}
