/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshein <lshein@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 06:09:56 by lshein            #+#    #+#             */
/*   Updated: 2025/03/03 06:19:07 by lshein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	check_redirection(char *arg)
{
	if (!arg)
		return (-1);
	if (ft_strcmp(">>", arg) == 0)
		return (APPEND);
	else if (ft_strcmp("<<", arg) == 0)
		return (HEREDOC);
	else if (ft_strcmp("<", arg) == 0)
		return (INPUT);
	else if (ft_strcmp(">", arg) == 0)
		return (OUTPUT);
	return (-1);
}

void	redirection_counter(t_minishell *data, t_ast_node *node, char **command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (ft_strcmp(command[i], "<<") == 0)
		{
			data->forking->heredoc_count++;
			node->redirection->heredoc_count++;
		}
		else if (ft_strcmp(command[i], "<") == 0 || ft_strcmp(command[i],
				">") == 0 || ft_strcmp(command[i], ">>") == 0)
		{
			data->forking->redirection_count++;
			node->redirection->redirection_count++;
		}
		i++;
	}
}

void	allocate_redirection_memory(t_ast_node *node)
{
	node->redirection->files = (char **)malloc(sizeof(char *)
			* (node->redirection->redirection_count + 1
				+ node->redirection->heredoc_count));
	node->redirection->types = (int *)malloc(sizeof(int)
			* (node->redirection->redirection_count + 1
				+ node->redirection->heredoc_count));
}

void	fill_redirection_data(t_minishell *data, t_ast_node *node,
		char **command)
{
	int	i;
	int	j;
	int	type;

	i = 0;
	j = 0;
	while (command[i])
	{
		type = check_redirection(command[i]);
		if (type != -1)
		{
			node->redirection->types[j] = type;
			if (data->args[i + 1])
			{
				node->redirection->files[j] = ft_strdup(command[i + 1]);
				i++;
			}
			else
				node->redirection->files[j] = NULL;
			j++;
		}
		i++;
	}
	node->redirection->types[j] = -1;
	node->redirection->files[j] = NULL;
}

void	init_redirection_data(t_minishell *data, t_ast_node *node,
		char **command)
{
	node->redirection = (t_redirections *)malloc(sizeof(t_redirections));
	node->redirection->redirection_count = 0;
	node->redirection->heredoc_count = 0;
	redirection_counter(data, node, command);
	allocate_redirection_memory(node);
	fill_redirection_data(data, node, command);
	node->redirection->heredoc_fd[0] = -1;
	node->redirection->heredoc_fd[1] = -1;
}
