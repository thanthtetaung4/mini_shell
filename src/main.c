/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshein <lshein@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:23:27 by taung             #+#    #+#             */
/*   Updated: 2024/12/23 16:13:24 by lshein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#include <readline/readline.h>
#include "../header/ast.h"
#include <stdio.h>

int main()
{
	// printf("hello world\n");
	// char *line = readline("Enter a line >>");
	// printf("%s\n", line);

	t_ast_node *node = create_node(PIPE, NULL);
	t_ast_node *end_node = create_node(COMMAND, "sort");
	t_ast_node *left_upper_node = create_node(PIPE, NULL);
	t_ast_node *left_node = create_node(COMMAND, "ls -l");
	t_ast_node *right_node = create_node(COMMAND, "grep .txt");

	add_right_node(&node, end_node);
	add_left_node(&node, left_upper_node);
	add_left_node((&left_upper_node), left_node);
	add_right_node((&left_upper_node), right_node);
	t_ast_node *temp = node;
	while (temp)
	{
		if (temp->type == PIPE)
		{
			printf("|\n");
		}
		if (temp->right)
		{
			printf("%s", temp->right->command);
		}
		if (temp->left)
		{
			if (temp->left->type == COMMAND)
			{
				printf("%s", temp->left->command);
				temp = NULL;
			}
			else
				temp = temp->left;
		}
		printf("\n");
	}
}
