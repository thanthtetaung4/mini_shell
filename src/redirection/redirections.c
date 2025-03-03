/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshein <lshein@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 05:50:46 by lshein            #+#    #+#             */
/*   Updated: 2025/03/03 05:56:12 by lshein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

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

int	heredoc(t_minishell *data, t_ast_node *node, int inside_pipe)
{
	char	**delimiters;
	int		result;

	(void)data;
	(void)inside_pipe;
	delimiters = get_heredoc_delimiters(node);
	if (!delimiters)
		return (EXIT_FAILURE);
	if (setup_heredoc_pipe(node) == EXIT_FAILURE)
	{
		free_heredoc(NULL, delimiters);
		return (EXIT_FAILURE);
	}
	result = read_heredoc_input(node, delimiters);
	close(node->redirection->heredoc_fd[1]);
	signal(SIGINT, handle_sigint);
	return (result);
}
