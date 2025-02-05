#include "../../header/minishell.h"

int check_redirections(char **command, t_minishell *data)
{
	int i;

	i = 0;
	if (!command || !command[i])
		return (-1);
	while (command && command[i])
	{
		if (ft_strcmp(">>", command[i]) == 0)
			return (APPEND);
		else if (ft_strcmp("<<", command[i]) == 0)
			return (HEREDOC);
		else if (ft_strcmp("<", command[i]) == 0)
			return (INPUT);
		else if (ft_strcmp(">", command[i]) == 0)
			return (OUTPUT);
		i++;
	}
	return (-1);
}
void redirection_counter(t_minishell *data, int type)
{
	if (type == HEREDOC)
		data->forking->heredoc_count++;
	else if (type == APPEND || type == INPUT || type == OUTPUT)
		data->forking->redirection_count++;
}
t_ast_node *create_node(int type, char **command, t_minishell *data, int count)
{
	t_ast_node *node;
	int i;

	i = 0;
	node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	node->executed = 0;
	node->type = type;
	if (node->type == COMMAND)
	{
		node->command = malloc(sizeof(char *) * count + 1);
		while (i < count)
		{
			node->command[i] = ft_strdup(command[i]);
			i++;
		}
		node->command[i] = NULL;
	}
	else
		node->command = NULL;
	node->redirection = check_redirections(command, data);
	redirection_counter(data, node->redirection);
	return node;
}

void add_right_node(t_ast_node **parent_node, t_ast_node *node)
{
	(*parent_node)->right = node;
	node->parent = *parent_node;
}

void add_left_node(t_ast_node **parent_node, t_ast_node *node)
{
	(*parent_node)->left = node;
	node->parent = *parent_node;
}
