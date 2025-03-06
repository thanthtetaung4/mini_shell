/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshein <lshein@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 02:16:36 by lshein            #+#    #+#             */
/*   Updated: 2025/03/06 02:21:37 by lshein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	is_only_quotes(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != '"' && input[i] != '\'')
			return (0);
		i++;
	}
	return (1);
}

void	open_file_empty_cmd(t_ast_node *node)
{
	int	i;
	int	fd;

	i = 0;
	while (node->redirection->files[i])
	{
		if (node->redirection->types[i] == APPEND
			|| node->redirection->types[i] == OUTPUT)
		{
			fd = open(node->redirection->files[i], O_WRONLY | O_CREAT | O_TRUNC,
					0644);
			if (fd != -1)
				close(fd);
		}
		i++;
	}
}

int	is_runable(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}
