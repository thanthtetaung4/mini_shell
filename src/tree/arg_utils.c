/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshein <lshein@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:38:14 by lshein            #+#    #+#             */
/*   Updated: 2025/03/04 14:39:40 by lshein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	**prepare_args_no_pipe(t_ast_node *node, t_minishell *data)
{
	char	**args;
	int		i;

	args = malloc(sizeof(char *) * (data->args_count + 1));
	if (!args)
		return (NULL);
	if (node->command[0][0] == '.' && node->command[0][1] == '/')
		validate_command_path(node->command[0], args, data);
	if (node->command[0][0] == '/')
		validate_command_path(node->command[0], args, data);
	if ((node->command[0][0] != '.' && node->command[0][1] != '/')
		&& ft_strncmp(node->command[0], "/bin/", 5) != 0)
		args[0] = find_command_path(node->command[0], data);
	else
		args[0] = ft_strdup(node->command[0]);
	i = 1;
	while (node->command[i])
	{
		args[i] = ft_strdup(node->command[i]);
		i++;
	}
	args[i] = NULL;
	return (args);
}

char	**prepare_args_with_pipe(t_ast_node *node, t_minishell *data)
{
	char	**args;
	int		i;

	args = malloc(sizeof(char *) * (data->args_count + 1));
	if (!args)
		return (NULL);
	if (node->command[0][0] == '.' && node->command[0][1] == '/')
		validate_command_path(node->command[0], args, data);
	if (node->command[0][0] == '/')
		validate_command_path(node->command[0], args, data);
	if ((node->command[0][0] != '.' && node->command[0][1] != '/')
		&& ft_strncmp(node->command[0], "/bin/", 5) != 0)
		args[0] = find_command_path(node->command[0], data);
	else
		args[0] = ft_strdup(node->command[0]);
	i = 1;
	while (i < data->args_count)
	{
		args[i] = ft_strdup(node->command[i]);
		i++;
	}
	args[i] = NULL;
	return (args);
}
