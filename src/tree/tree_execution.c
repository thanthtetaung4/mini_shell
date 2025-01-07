#include "../../header/ast.h"
#include "../../header/minishell.h"

void tree_execution(t_ast_node *lowest_node)
{
	t_ast_node *node;
	t_ast_node *temp_node;

	node = lowest_node;
	temp_node = NULL;
	while (node)
	{
		if (node->type == COMMAND)
		{
			node->executed = 1;
			printf("%s is executed.\n", node->command);
			node = node->parent;
		}
		else if (node->type == PIPE)
		{
			temp_node = node->right;
			if (temp_node->executed == 0)
			{
				printf("%s is executed.\n", temp_node->command);
				temp_node->executed = 1;
				node = node->parent;
			}
			else
			{
				node = node->parent;
			}
		}
	}
}
