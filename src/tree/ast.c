/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 06:10:44 by lshein            #+#    #+#             */
/*   Updated: 2025/03/07 23:46:44 by taung            ###   ########.fr       */
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
	node->cmd_count = 0;
	return (node);
}

void	fill_command_data(t_ast_node *node, char **command,
		int count)
{
	int	iterator[2];

	iterator[0] = 0;
	iterator[1] = 0;
	node->command = malloc(sizeof(char *) * (count + 1));
	if (!node->command)
		return ;
	while (iterator[1] < count && command[iterator[0]])
	{
		if (check_redirection(command[iterator[0]]) != -1
			&& command[iterator[0] + 1])
			iterator[0]++;
		else if (check_redirection(command[iterator[0]]) == -1)
		{
			fill_cmd_data_helper(node, command, iterator, count);
			if (!node->command[iterator[1]])
				return ;
			iterator[1]++;
		}
		iterator[0]++;
	}
	node->command[iterator[1]] = NULL;
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
		node->cmd_count = ft_count_tds(node->command);
		ft_interpret(data, node);
		remove_empty_args(node);
		remove_cmd_quote(node);
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
