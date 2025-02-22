#include "../../header/minishell.h"

void free_tree_helper(t_ast_node *node)
{
    int i;

    if (!node)
        return;
    if (node->left)
        free_tree_helper(node->left);
    if (node->right)
        free_tree_helper(node->right);
    if (node->type == COMMAND && node->command)
    {
        i = 0;
        while (node->command[i])
        {
            free(node->command[i]);
            i++;
        }
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
void	reset_forking_data(t_minishell *data)
{
	int i;

	i = 0;
	if (data->forking->fds && data->forking->fds[i])
	{
		while (i < data->forking->i_fd)
		{
            free(data->forking->fds[i]);
            i++;
		}
        // printf("fds\n");
		free(data->forking->fds);
    }
    if (data->forking->pids)
        free(data->forking->pids);
    if (data->forking->redirection_fds)
        free(data->forking->redirection_fds);
    data->forking->i_fd = 0;
    data->forking->i_pid = 0;
    data->forking->i_rfd = 0;
    data->forking->pipe_count = 0;
    data->forking->redirection_count = 0;
    data->forking->completed_piping = 0;
    data->forking->heredoc_count = 0;
}
