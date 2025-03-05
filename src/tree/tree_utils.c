/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshein <lshein@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 06:41:14 by lshein            #+#    #+#             */
/*   Updated: 2025/03/03 11:39:39 by lshein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	check_cmd(char *cmd)
{
	char	*bultins[8];
	int		i;

	i = 0;
	bultins[0] = "cd";
	bultins[1] = "echo";
	bultins[2] = "env";
	bultins[3] = "exit";
	bultins[4] = "pwd";
	bultins[5] = "unset";
	bultins[6] = "export";
	bultins[7] = NULL;
	while (bultins[i] != NULL)
	{
		if (ft_strcmp(bultins[i], cmd) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	save_std_fds(t_ast_node *node, int *stdout_fd, int *stdin_fd)
{
	int	i;

	i = 0;
	*stdout_fd = -1;
	*stdin_fd = -1;
	while (node->redirection->types[i] != -1
		&& node->redirection->files[i] != NULL)
	{
		if (node->redirection->types[i] == OUTPUT
			|| node->redirection->types[i] == APPEND)
		{
			if (*stdout_fd != -1)
				close(*stdout_fd);
			*stdout_fd = dup(STDOUT_FILENO);
		}
		else if (node->redirection->types[i] == INPUT
			|| node->redirection->types[i] == HEREDOC)
		{
			if (*stdin_fd != -1)
				close(*stdin_fd);
			*stdin_fd = dup(STDIN_FILENO);
		}
		i++;
	}
}

void	restore_std_fds(int stdout_fd, int stdin_fd)
{
	if (stdout_fd != -1)
	{
		dup2(stdout_fd, STDOUT_FILENO);
		close(stdout_fd);
	}
	if (stdin_fd != -1)
	{
		dup2(stdin_fd, STDIN_FILENO);
		close(stdin_fd);
	}
}
