/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 06:10:44 by lshein            #+#    #+#             */
/*   Updated: 2025/03/06 01:31:38 by taung            ###   ########.fr       */
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
int	is_only_quotes (char *input)
{
	int	i;

	i = 0;
	while(input[i])
	{
		if(input[i] != '"' && input[i] != '\'')
			return (0);
		i++;
	}
	return (1);
}
void	fill_command_data(t_minishell *data,t_ast_node *node, char **command, int count)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	(void)data;
	node->command = malloc(sizeof(char *) * (count + 1));
	if (!node->command)
		return ;
	while (j < count && command[i])
	{
		if (check_redirection(command[i]) != -1 && command[i + 1])
			i++;
		else if (check_redirection(command[i]) == -1)
		{
			if (is_only_quotes(command[i]))
				node->command[j] = ft_strdup(" ");
			else
				node->command[j] = ft_strdup(command[i]);
			if (!node->command[j])
			return ;
			j++;
		}
		i++;
	}
	node->command[j] = NULL;
	node->cmd_count = ft_count_tds(node->command);
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
		fill_command_data(data, node, command, count);
		ft_interpret(data, node);
		remove_cmd_quote(node);
		remove_empty_args(node);
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
