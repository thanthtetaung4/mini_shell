/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 05:50:46 by lshein            #+#    #+#             */
/*   Updated: 2025/03/07 23:31:48 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	handle_heredoc_input(t_minishell *data, t_ast_node *node,
		t_heredoc *heredoc)
{
	while (1)
	{
		heredoc->line = readline("> ");
		if (g_sig_status == 1)
		{
			data->status = 130;
			free(heredoc->line);
			break ;
		}
		if (!(heredoc->line))
		{
			if (heredoc->current_delimiter < node->redirection->heredoc_count
				- 1)
			{
				(heredoc->current_delimiter)++;
				continue ;
			}
			break ;
		}
		handle_heredoc_input_helper(heredoc, node, data);
		if (heredoc->current_delimiter == node->redirection->heredoc_count)
			break ;
	}
	rl_event_hook = NULL;
	free_heredoc(NULL, heredoc->delimiter);
}

int	heredoc(t_minishell *data, t_ast_node *node)
{
	t_heredoc	*heredoc;

	heredoc = malloc(sizeof(t_heredoc));
	init_heredoc(heredoc);
	init_delimiters(node, heredoc);
	if (setup_heredoc_pipe(node->redirection->heredoc_fd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	g_sig_status = 0;
	set_signals_heredoc();
	handle_heredoc_input(data, node, heredoc);
	close(node->redirection->heredoc_fd[1]);
	signal(SIGINT, handle_sigint);
	free(heredoc);
	return (g_sig_status);
}
