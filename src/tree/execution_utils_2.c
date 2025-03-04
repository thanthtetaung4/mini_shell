/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:03:50 by lshein            #+#    #+#             */
/*   Updated: 2025/03/04 21:31:08 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	setup_child_process(t_minishell *data, t_ast_node *node)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (node->redirection->types[0] != -1)
	{
		if (execute_redirection(node, data))
		{
			free_all(data, 1);
			exit(1);
		}
	}
	execute_command(data, node);
}

int	handle_child_exit_status(int exit_status)
{
	int	sig;

	if (WIFSIGNALED(exit_status))
	{
		sig = WTERMSIG(exit_status);
		if (sig == SIGQUIT)
		{
			write(1, "Quit: (Core dumped)\n", 20);
			return (128 + sig);
		}
		else if (sig == SIGINT)
		{
			write(1, "\n", 1);
			return (128 + sig);
		}
	}
	else if (WIFEXITED(exit_status))
	{
		return (WEXITSTATUS(exit_status));
	}
	return (exit_status);
}

void	handle_empty_command_child(t_minishell *data)
{
	close(data->forking->fds[data->forking->i_fd][0]);
	close(data->forking->fds[data->forking->i_fd][1]);
	close_heredoc_fds_p(data);
	free_all(data, 1);
	exit(0);
}

void	update_empty_prev_node(t_minishell *data, t_ast_node *node)
{
	if (!node->command[0] && node->redirection->heredoc_count > 0)
		data->empty_prev_node = 1;
	else
		data->empty_prev_node = 0;
}

int	handle_command_heredoc(t_minishell *data, t_ast_node *node)
{
	int	sig;

	sig = 0;
	if (node->type == COMMAND && node->redirection
		&& node->redirection->heredoc_count > 0)
	{
		sig = heredoc(data, node);
	}
	return (sig);
}
