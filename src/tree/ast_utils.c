#include "../../header/ast.h"
#include "../../header/minishell.h"

t_ast_node *create_node(int type, char *command)
{
	t_ast_node *node;

	node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	node->executed = 0;
	node->depth_level = 0;
	node->type = type;
	node->command = command;
	return node;
}

void add_right_node(t_ast_node **parent_node, t_ast_node *node)
{
	(*parent_node)->right = node;
	node->parent = *parent_node;
	node->depth_level = (*parent_node)->depth_level + 1;
}

void add_left_node(t_ast_node **parent_node, t_ast_node *node)
{
	(*parent_node)->left = node;
	node->parent = *parent_node;
	node->depth_level = (*parent_node)->depth_level + 1;
}
