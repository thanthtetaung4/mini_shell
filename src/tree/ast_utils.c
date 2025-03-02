#include "../../header/minishell.h"

int	check_redirection(char *arg)
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

void	redirection_counter(t_minishell *data, t_ast_node *node, char **command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (ft_strcmp(command[i], "<<") == 0)
		{
			data->forking->heredoc_count++;
			node->redirection->heredoc_count++;
		}
		else if (ft_strcmp(command[i], "<") == 0 || ft_strcmp(command[i],
				">") == 0 || ft_strcmp(command[i], ">>") == 0)
		{
			data->forking->redirection_count++;
			node->redirection->redirection_count++;
		}
		i++;
	}
}

void	allocate_redirection_memory(t_ast_node *node)
{
	node->redirection->files = (char **)malloc(sizeof(char *)
			* (node->redirection->redirection_count + 1
				+ node->redirection->heredoc_count));
	node->redirection->types = (int *)malloc(sizeof(int)
			* (node->redirection->redirection_count + 1
				+ node->redirection->heredoc_count));
}

void	fill_redirection_data(t_minishell *data, t_ast_node *node,
		char **command)
{
	int	i;
	int	j;
	int	type;

	i = 0;
	j = 0;
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

void	init_redirection_data(t_minishell *data, t_ast_node *node,
		char **command)
{
	node->redirection = (t_redirections *)malloc(sizeof(t_redirections));
	node->redirection->redirection_count = 0;
	node->redirection->heredoc_count = 0;
	redirection_counter(data, node, command);
	allocate_redirection_memory(node);
	fill_redirection_data(data, node, command);
	node->redirection->heredoc_fd[0] = -1;
	node->redirection->heredoc_fd[1] = -1;
}

t_ast_node	*allocate_node(int type)
{
	t_ast_node	*node;

	node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	node->executed = 0;
	node->command = NULL;
	return (node);
}

void	fill_command_data(t_ast_node *node, char **command, int count)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	node->command = malloc(sizeof(char *) * (count + 1));
	if (!node->command)
		return ;
	while (j < count && command[i])
	{
		if (check_redirection(command[i]) != -1 && command[i + 1])
			i++;
		else if (check_redirection(command[i]) == -1)
		{
			node->command[j] = ft_strdup(command[i]);
			if (!node->command[j])
				return ;
			j++;
		}
		i++;
	}
	node->command[j] = NULL;
}

t_ast_node	*create_node(int type, char **command, t_minishell *data, int count)
{
	t_ast_node	*node;

	node = allocate_node(type);
	if (!node)
		return (NULL);
	if (node->type == COMMAND)
	{
		init_redirection_data(data, node, command);
		if (node->redirection->redirection_count != 0
			|| node->redirection->heredoc_count != 0)
			count -= (2 * node->redirection->redirection_count) + (2
					* node->redirection->heredoc_count);
		fill_command_data(node, command, count);
	}
	return (node);
}

void	add_right_node(t_ast_node **parent_node, t_ast_node *node)
{
	(*parent_node)->right = node;
	node->parent = *parent_node;
}

void	add_left_node(t_ast_node **parent_node, t_ast_node *node)
{
	(*parent_node)->left = node;
	node->parent = *parent_node;
}
