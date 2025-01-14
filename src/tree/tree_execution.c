#include "../../header/minishell.h"

int tree_execution(t_ast_node *lowest_node, t_minishell *data)
{
	t_ast_node *node;
	t_ast_node *temp_node;
	//
	int i;
	i = 0;
	//
	node = lowest_node;
	temp_node = NULL;
	while (node)
	{
		if (node->type == COMMAND)
		{
			node->executed = 1;
			//
			ft_exec(node->command, data);
			// while (node->command[i])
			// {
			// 	printf("%s ", node->command[i]);
			// 	i++;
			// }
			// printf("is executed.\n");
			//
			node = node->parent;
		}
		else if (node->type == PIPE)
		{
			temp_node = node->right;
			if (temp_node->executed == 0)
			{
				//
				i = 0;
				while (temp_node->command[i])
				{
					printf("%s ", temp_node->command[i]);
					i++;
				}
				printf("is executed.\n");
				//
				temp_node->executed = 1;
				node = node->parent;
			}
			else
				node = node->parent;
		}
	}
	return (0);
}
