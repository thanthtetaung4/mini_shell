/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 07:22:33 by taung             #+#    #+#             */
/*   Updated: 2025/03/06 07:25:48 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

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
		if (j == node->redirection->heredoc_count - 1
			&& (node->redirection->files[i][0] == '\''
			|| node->redirection->files[i][0] == '"'))
			heredoc->is_expend = 0;
		if (node->redirection->types[i] == HEREDOC)
			heredoc->delimiter[j++]
				= remove_quote_hd(node->redirection->files[i]);
		i++;
	}
	heredoc->delimiter[j] = NULL;
}
