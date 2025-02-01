#include "../../header/minishell.h"

void free_tree(t_ast_node *node)
{
    t_ast_node *current, *parent;

    if (!node)
        return;

    current = node;
    
    // Traverse up to the root
    while (current->parent)
        current = current->parent;
    
    // Now free the tree starting from the root
	if (current->left)
    	free_tree(current->left);
	if (current->right)
    	free_tree(current->right);

    // Free the command arguments array
    if (current->command)
    {
        for (int i = 0; current->command[i]; i++)
            free(current->command[i]);
        free(current->command);
    }
    // Free the node itself
    free(current);
}
