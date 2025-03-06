/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshein <lshein@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 06:09:56 by lshein            #+#    #+#             */
/*   Updated: 2025/03/06 02:18:02 by lshein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	allocate_redirection_memory(t_ast_node *node)
{
	node->redirection->files = (char **)malloc(sizeof(char *)
			* (node->redirection->redirection_count + 1
				+ node->redirection->heredoc_count));
	node->redirection->types = (int *)malloc(sizeof(int)
			* (node->redirection->redirection_count + 1
				+ node->redirection->heredoc_count));
}

int	file_quote_count(char *file)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (file[i])
	{
		if (file[i] == '\'' || file[i] == '"')
			c++;
		i++;
	}
	return (c);
}

char	*remove_quote_f(char *file, int type)
{
	char	*new_file;
	int		i;
	int		j;
	int		q_c;

	i = 0;
	j = 0;
	q_c = file_quote_count(file);
	if (q_c > 0 && type != HEREDOC)
		new_file = malloc(sizeof(char *) * (ft_strlen(file) - q_c + 1));
	else
		return (ft_strdup(file));
	while (file[i])
	{
		if (file[i] != '\'' && file[i] != '"')
		{
			new_file[j] = file[i];
			j++;
		}
		i++;
	}
	new_file[j] = '\0';
	return (new_file);
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
				node->redirection->files[j] = remove_quote_f(command[i + 1], type);
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
