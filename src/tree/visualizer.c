#include "../header/minishell.h"

void print_command(t_ast_node *node)
{
    int i = 0;
    printf("COMMAND: ");
    if (node->command)
    {
        while (node->command[i])
        {
            printf("%s ", node->command[i]);
            i++;
        }
    }
    printf("\n");
}

void print_node_type(t_ast_node *node)
{
    if (node->type == COMMAND)
        print_command(node);
    else if (node->type == PIPE)
        printf("PIPE\n");
    else if (node->type == HEREDOC)
        printf("HEREDOC\n");
    else if (node->type == APPEND)
        printf("APPEND\n");
    else if (node->type == INPUT)
        printf("INPUT\n");
    else if (node->type == OUTPUT)
        printf("OUTPUT\n");
}

void print_branch(t_ast_node *node, int depth, const char *direction)
{
    if (!node)
        return;

    for (int i = 0; i < depth; i++)
        printf("  ");

    printf("%s", direction);
    print_node_type(node);

    print_branch(node->left, depth + 1, "L-");
    print_branch(node->right, depth + 1, "R-");
}

// Entry function to visualize the tree including all sub-branches
t_ast_node *find_root(t_ast_node *node)
{
	while (node && node->parent)
		node = node->parent;
	return node;
}

// Entry function to visualize the tree including all sub-branches
void visualize_tree(t_ast_node *lowest_node)
{
	if (!lowest_node)
	{
		printf("The tree is empty.\n");
		return ;
	}
	t_ast_node *root = find_root(lowest_node);
	printf("Abstract Syntax Tree (From Root Including All Branches):\n");
	print_branch(root, 0, "Root-");
}
