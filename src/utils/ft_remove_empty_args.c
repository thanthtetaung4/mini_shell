/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_empty_args.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshein <lshein@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:54:30 by taung             #+#    #+#             */
/*   Updated: 2025/03/07 07:51:39 by lshein           ###   ########.fr       */
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

int check_for_output(t_ast_node *node)
{
	int i;

	i = 0;
	while(node->redirection->types[i] != -1)
	{
		if (node->redirection->types[i] == OUTPUT || node->redirection->types[i] == APPEND)
			return (1);
		i++;
	}
	return (0);
}

int check_for_input(t_ast_node *node)
{
	int i;

	i = 0;
	while(node->redirection->types[i] != -1)
	{
		if (node->redirection->types[i] == INPUT || node->redirection->types[i] == HEREDOC)
			return (1);
		i++;
	}
	return (0);
}

