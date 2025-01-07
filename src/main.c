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

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		char *input = argv[1];
		t_ast_node *root = create_tree(input);

		printf("Visualizing the AST for input: %s\n", input);
		visualize_tree(root);
		tree_execution(root);
	}
	return 0;
}
