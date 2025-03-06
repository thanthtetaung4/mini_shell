/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshein <lshein@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 02:07:32 by lshein            #+#    #+#             */
/*   Updated: 2025/03/06 02:08:07 by lshein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	check_valid_args(char *arg)
{
	int	i;
	int	sign;

	if (!arg)
		return (0);
	i = 0;
	sign = 0;
	if (arg[i] == '-' || arg[i] == '+')
	{
		sign = 1;
		i++;
	}
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	if (sign && i == 1)
		return (0);
	return (1);
}

/**
 * Handles exiting with no arguments
 */
static void	handle_simple_exit(t_minishell *data)
{
	free_all(data, 1);
	ft_putstr_fd("exit\n", 0);
	exit(0);
}

/**
 * Handles exiting with a single numeric argument
 */
static void	handle_numeric_exit(t_minishell *data, char *arg)
{
	int	exit_status;

	exit_status = ft_atoi(arg);
	free_all(data, 1);
	exit(exit_status % 256);
}

/**
 * Handles exiting with an invalid numeric argument
 */
static void	handle_invalid_exit(t_minishell *data, char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	free_all(data, 1);
	exit(2);
}

/**
 * Main exit function - handles the 'exit' builtin command
 */
void	ft_exit(t_minishell *data, t_ast_node *node)
{
	int	cmd_count;

	cmd_count = ft_count_tds(node->command);
	if (!node->command[1])
		handle_simple_exit(data);
	else if (cmd_count == 2)
	{
		if (check_valid_args(node->command[1]))
			handle_numeric_exit(data, node->command[1]);
		else
			handle_invalid_exit(data, node->command[1]);
	}
	else
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
}
