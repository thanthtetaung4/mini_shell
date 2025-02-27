#include "../../header/minishell.h"

void print_strs(char **strs);

int check_redirection(char *arg)
{
	if (!arg)
		return (-1);
	if (ft_strcmp(">>", arg) == 0)
		return (APPEND);
	else if (ft_strcmp("<<", arg) == 0)
		return (HEREDOC);
	else if (ft_strcmp("<", arg) == 0)
		return (INPUT);
	else if (ft_strcmp(">", arg) == 0)
		return (OUTPUT);
	return (-1);
}
void redirection_counter(t_minishell *data, t_ast_node *node, char **command)
{
	int i;

	i = 0;
	// printf("recommand);
	while (command[i])
	{
		if (ft_strcmp(command[i], "<<") == 0)
		{
			data->forking->heredoc_count++;
			node->redirection->heredoc_count++;
		}
		else if (ft_strcmp(command[i], "<") == 0 || ft_strcmp(command[i], ">") == 0 || ft_strcmp(command[i], ">>") == 0)
		{
			data->forking->redirection_count++;
			node->redirection->redirection_count++;
			// printf("%d,%d\n",data->forking->redirection_count, node->redirection->redirection_count);
		}
		i++;
	}
}

void init_redirection_data(t_minishell *data, t_ast_node *node, char **command)
{
	int i;
	int j;
	int type;

	i = 0;
	j = 0;
	type = -1;
	node->redirection = (t_redirections *)malloc(sizeof(t_redirections));
	node->redirection->redirection_count = 0;
	node->redirection->heredoc_count = 0;
	redirection_counter(data, node, command);
	// printf("count : %d\n", node->redirection->redirection_count);
	node->redirection->files = (char **)malloc(sizeof(char *) * (node->redirection->redirection_count + 1 + node->redirection->heredoc_count));
	node->redirection->types = (int *)malloc(sizeof(int) * (node->redirection->redirection_count + 1 + node->redirection->heredoc_count));
	while (command[i])
	{
		type = check_redirection(command[i]);
		if (type != -1)
		{
			node->redirection->types[j] = type;
			if (data->args[i + 1])
			{
				node->redirection->files[j] = ft_strdup(command[i + 1]);
				i++;
			}
			else
				node->redirection->files[j] = NULL;
			j++;
		}
		i++;
	}
	node->redirection->types[j] = -1;
	node->redirection->files[j] = NULL;
}

void print_strs(char **strs)
{
    int i = 0;
	printf("--------=\n");
    while (strs[i])
    {
        printf("%s\n", strs[i]);
        i++;
    }
	printf("--------=\n");
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
	node->type = type;
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	// printf("%s\n", command[0]);
	node->executed = 0;
	node->command = NULL;
	if (node->type == COMMAND)
	{
		// print_strs(command);
		init_redirection_data(data, node, command);
		// printf("________\n");
		// printf("%s\n", command[0]);
		// printf("r count %d\n", data->forking->redirection_count);
		// printf("initial %d\n", count);
		if (node->redirection->redirection_count != 0 || node->redirection->heredoc_count != 0)
			count -= (2 * node->redirection->redirection_count) + (2 * node->redirection->heredoc_count);
		// printf("after %d\n", count);
		// printf("________\n");
		node->command = malloc(sizeof(char *) * (count + 1));
		// printf("%d\n", count);
		if (!node->command)
			return (NULL);
		while (j < count && command[i])
		{
			// printf("cmd %i: %s\n",i, command[i]);
			if (check_redirection(command[i]) != -1 && command[i + 1])
				i++;
			else if (check_redirection(command[i]) == -1)
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
	// printf("ok\n");
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
