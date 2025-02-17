/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 05:36:02 by taung             #+#    #+#             */
/*   Updated: 2025/02/05 10:58:45 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_echo(t_minishell *data, t_ast_node *node)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if (node->command[i] && ft_strcmp(node->command[i], "-n") == 0)
	{
		n_flag = 1;
		i++;
	}
	while (node->command[i])
	{
		ft_putstr_fd(node->command[i], 1);
		if (node->command[i + 1])
		ft_putstr_fd(" ", 1);
		i++;
	}
	if (!n_flag)
	ft_putstr_fd("\n", 1);

	// data->forking->completed_piping++;
	return (0);
}
// add echo $HOME with "" & wuthout quote reaplce with env value and with '' doesn't replace with env value
