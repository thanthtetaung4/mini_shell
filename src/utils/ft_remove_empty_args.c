/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_empty_args.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:54:30 by taung             #+#    #+#             */
/*   Updated: 2025/03/02 15:54:36 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	empty_args_count(char **args)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (ft_strlen(args[i]) == 0)
			count++;
		i++;
	}
	return (count);
}

void	remove_empty_args(t_ast_node *node)
{
	int		i;
	int		count;
	char	**new_args;

	i = 0;
	count = empty_args_count(node->command);
	new_args = malloc(sizeof(char *) * (node->cmd_count - count + 1));
	if (!new_args)
		return ;
	i = 0;
	count = 0;
	while (node->command[i])
	{
		if (ft_strlen(node->command[i]) != 0)
		{
			new_args[i - count] = ft_strdup(node->command[i]);
		}
		else
			count++;
		i++;
	}
	new_args[i - count] = NULL;
	free_2d_string(node->command);
	node->command = new_args;
	node->cmd_count = node->cmd_count - count;
}
