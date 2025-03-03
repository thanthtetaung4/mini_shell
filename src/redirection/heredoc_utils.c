/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 05:52:50 by lshein            #+#    #+#             */
/*   Updated: 2025/03/03 15:05:15 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

extern	int	g_sig_status;

void	free_heredoc(char *line, char **delimiters)
{
	int	i;

	i = 0;
	free(line);
	while (delimiters[i])
	{
		free(delimiters[i]);
		i++;
	}
	free(delimiters);
}

void	init_delimiters(t_ast_node *node, t_heredoc *heredoc)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	heredoc->delimiter = malloc(sizeof(char *)
			* (node->redirection->heredoc_count + 1));
	while (node->redirection->types[i] && node->redirection->files[i])
	{
		if (node->redirection->types[i] == HEREDOC)
			heredoc->delimiter[j++] = ft_strdup(node->redirection->files[i]);
		i++;
	}
	heredoc->delimiter[j] = NULL;
}

int	setup_heredoc_pipe(int *heredoc_fd)
{
	if (pipe(heredoc_fd) == -1)
	{
		perror("pipe");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	handle_heredoc_input_helper(t_heredoc *heredoc, t_ast_node *node,
		t_minishell *data)
{
	char	*tmp;

	if (ft_strcmp(heredoc->line,
			heredoc->delimiter[heredoc->current_delimiter]) == 0)
		(heredoc->current_delimiter)++;
	else if (heredoc->current_delimiter == node->redirection->heredoc_count - 1
		&& node->command[0])
	{
		tmp = heredoc->line;
		heredoc->line = ft_interpret_str(data, heredoc->line);
		free(tmp);
		ft_putstr_fd(heredoc->line, node->redirection->heredoc_fd[1]);
		ft_putstr_fd("\n", node->redirection->heredoc_fd[1]);
	}
	free(heredoc->line);
}

void	init_heredoc(t_heredoc *heredoc)
{
	heredoc->current_delimiter = 0;
	heredoc->line = NULL;
}
