#include "../../header/minishell.h"

void free_tree_helper(t_ast_node *node)
{
    if (!node)
        return;
    free_tree_helper(node->left);
    free_tree_helper(node->right);
    if (node->type == COMMAND && node->command)
    {
        for (int i = 0; node->command[i]; i++)
            free(node->command[i]);
        free(node->command); 
    }
    free(node);
}

void free_tree(t_ast_node *node)
{
    t_ast_node *root;

    if (!node)
        return;
    root = node;
    while (root->parent)
        root = root->parent;
    free_tree_helper(root);
}

