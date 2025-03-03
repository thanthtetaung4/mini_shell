/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshein <lshein@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 05:52:50 by lshein            #+#    #+#             */
/*   Updated: 2025/03/03 11:37:37 by lshein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int extern	g_sig_status;

char	**get_heredoc_delimiters(t_ast_node *node)
{
	char	**delimiters;
	int		i;
	int		j;

	i = 0;
	j = 0;
	delimiters = malloc(sizeof(char *) * (node->redirection->heredoc_count
				+ 1));
	if (!delimiters)
		return (NULL);
	while (node->redirection->types[i] && node->redirection->files[i])
	{
		if (node->redirection->types[i] == HEREDOC)
		{
			delimiters[j] = ft_strdup(node->redirection->files[i]);
			j++;
		}
		i++;
	}
	delimiters[j] = NULL;
	return (delimiters);
}

int	setup_heredoc_pipe(t_ast_node *node)
{
	if (pipe(node->redirection->heredoc_fd) == -1)
	{
		perror("pipe");
		return (EXIT_FAILURE);
	}
	g_sig_status = 0;
	set_signals_heredoc();
	return (EXIT_SUCCESS);
}

int	process_delimiter_match(char *line, char **delimiters,
		int *current_delimiter, int heredoc_count)
{
	if (ft_strcmp(line, delimiters[*current_delimiter]) == 0)
	{
		free(delimiters[*current_delimiter]);
		(*current_delimiter)++;
		if (*current_delimiter == heredoc_count)
		{
			return (1);
		}
	}
	return (0);
}

void	write_to_heredoc(char *line, t_ast_node *node, int current_delimiter)
{
	if ((current_delimiter == (node->redirection->heredoc_count - 1))
		&& ft_strcmp(line, node->redirection->files[current_delimiter]) != 0
		&& node->command[0])
	{
		ft_putstr_fd(line, node->redirection->heredoc_fd[1]);
		ft_putstr_fd("\n", node->redirection->heredoc_fd[1]);
	}
}

int	read_heredoc_input(t_ast_node *node, char **delimiters)
{
	char	*line;
	int		current_delimiter;

	current_delimiter = 0;
	while (1)
	{
		line = readline("> ");
		if (!line || g_sig_status == 1)
		{
			if (g_sig_status == 1)
				free(line);
			free_heredoc(NULL, delimiters);
			break ;
		}
		if (process_delimiter_match(line, delimiters, &current_delimiter,
				node->redirection->heredoc_count))
		{
			free(delimiters);
			free(line);
			break ;
		}
		write_to_heredoc(line, node, current_delimiter);
		free(line);
	}
	return (g_sig_status);
}
