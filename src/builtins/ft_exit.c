/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 07:14:56 by taung             #+#    #+#             */
/*   Updated: 2025/01/09 07:51:34 by taung            ###   ########.fr       */
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

void	ft_exit(t_minishell *data, char **args)
{
	if (!args[1])
	{
		free_all(data, args);
		ft_putstr_fd("exit\n",0);
		exit(0);
	}
	else if (args[1])
	{
		if (!check_valid_args(args[1]))
		{
			ft_putstr_fd("exit: ", 1);
			ft_putstr_fd(args[1], 1);
			ft_putstr_fd(": numeric argument require\n", 1);
			free_all(data, args);
			exit(1);
		}
		else
		{
			free_all(data, args);
			exit(1);
		}
	}
	else if (args[2])
	{
		ft_putstr_fd("exit: too many arguments\n",0);
	}
}
