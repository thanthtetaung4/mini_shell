#include "../../header/minishell.h"

int check_redirections(char **command, t_minishell *data, t_ast_node *node)
{
	int i;

	i = 0;
	if (!command || !command[i])
		return (-1);
	while (command && command[i])
	{
		// printf("cmd: %s\n", command[i]);
		if (ft_strcmp(">>", command[i]) == 0)
		{
			node->file = command[i + 1];
			return (APPEND);
		}
		else if (ft_strcmp("<<", command[i]) == 0)
		{
			node->file = command[i + 1];;
			return (HEREDOC);
		}
		else if (ft_strcmp("<", command[i]) == 0)
		{
			// printf("input found file:%s\n", command[i + 1]);
			node->file = command[i + 1];
			return (INPUT);
		}
		else if (ft_strcmp(">", command[i]) == 0)
		{
			// printf("output found file: %s\n", command[i + 1]);
			node->file = command[i + 1];
			return (OUTPUT);
		}

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
	int j;

	i = 0;
	j = 0;
	node = NULL;
	node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	node->file = NULL;
	node->executed = 0;
	node->type = type;
	node->redirection = check_redirections(command, data, node);
	redirection_counter(data, node->redirection);
	if (node->type == COMMAND)
	{
		node->command = NULL;
		if (node->redirection != -1)
		{
			count -= 2;
		}
		node->command = malloc(sizeof(char *) * (count + 1));
		if (!node->command)
			return (NULL);
		while (i < count)
		{
			if ((command[i][0] == '>' || command[i][0] == '<') && command[i + 1] && ft_strcmp(command[i + 1], node->file) == 0)
				i++;
			else
			{
				node->command[j] = ft_strdup(command[i]);
				if (!node->command[j])
					return (NULL); 
				j++;
			}
			i++;
		}
		node->command[j] = NULL;
	}
	else
		node->command = NULL;
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
