/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 15:27:47 by taung             #+#    #+#             */
/*   Updated: 2025/03/02 15:45:24 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_exec(t_minishell *data, t_ast_node *node)
{
	if (ft_strncmp(node->command[0], "env", ft_strlen(node->command[0])) == 0)
		print_env(&data->env);
	if (ft_strncmp(node->command[0], "export",
			ft_strlen(node->command[0])) == 0)
		return (ft_export(data, node));
	if (ft_strncmp(node->command[0], "unset", ft_strlen(node->command[0])) == 0)
		return (ft_unset(data));
	if (ft_strncmp(node->command[0], "exit", ft_strlen(node->command[0])) == 0)
	{
		ft_exit(data);
		return (1);
	}
	if (ft_strncmp(node->command[0], "pwd", ft_strlen(node->command[0])) == 0)
		return (ft_pwd());
	if (ft_strncmp(node->command[0], "cd", ft_strlen(node->command[0])) == 0)
		return (ft_cd(data));
	if (ft_strncmp(node->command[0], "echo", ft_strlen(node->command[0])) == 0)
		return (ft_echo(data, node));
	return (0);
}
