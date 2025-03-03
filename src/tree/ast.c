/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshein <lshein@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 06:10:44 by lshein            #+#    #+#             */
/*   Updated: 2025/03/03 06:19:11 by lshein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_ast_node	*allocate_node(int type)
{
	t_ast_node	*node;

	node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	node->executed = 0;
	node->command = NULL;
	return (node);
}

void	fill_command_data(t_ast_node *node, char **command, int count)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	node->command = malloc(sizeof(char *) * (count + 1));
	if (!node->command)
		return ;
	while (j < count && command[i])
	{
		if (check_redirection(command[i]) != -1 && command[i + 1])
			i++;
		else if (check_redirection(command[i]) == -1)
		{
			node->command[j] = ft_strdup(command[i]);
			if (!node->command[j])
				return ;
			j++;
		}
		i++;
	}
	node->command[j] = NULL;
}

t_ast_node	*create_node(int type, char **command, t_minishell *data, int count)
{
	t_ast_node	*node;

	node = allocate_node(type);
	if (!node)
		return (NULL);
	if (node->type == COMMAND)
	{
		init_redirection_data(data, node, command);
		if (node->redirection->redirection_count != 0
			|| node->redirection->heredoc_count != 0)
			count -= (2 * node->redirection->redirection_count) + (2
					* node->redirection->heredoc_count);
		fill_command_data(node, command, count);
	}
	return (node);
}

void	add_right_node(t_ast_node **parent_node, t_ast_node *node)
{
	(*parent_node)->right = node;
	node->parent = *parent_node;
}

void	add_left_node(t_ast_node **parent_node, t_ast_node *node)
{
	(*parent_node)->left = node;
	node->parent = *parent_node;
}
