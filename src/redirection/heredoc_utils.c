/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshein <lshein@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 05:52:50 by lshein            #+#    #+#             */
/*   Updated: 2025/03/06 02:59:09 by lshein           ###   ########.fr       */
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

char	*remove_quote_hd(char *file)
{
	char	*new_file;
	int		i;
	int		j;
	int		q_c;

	i = 0;
	j = 0;
	q_c = file_quote_count(file);
	if (q_c > 0)
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
		if (j == node->redirection->heredoc_count -1 && (node->redirection->files[i][0] == '\'' || node->redirection->files[i][0] == '"'))
			heredoc->is_expend = 0;
		if (node->redirection->types[i] == HEREDOC)
			heredoc->delimiter[j++] = remove_quote_hd(node->redirection->files[i]);
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
		if (heredoc->is_expend == 1)
		{
			tmp = heredoc->line;
			heredoc->line = ft_interpret_str(data, heredoc->line);
			free(tmp);
		}
		ft_putstr_fd(heredoc->line, node->redirection->heredoc_fd[1]);
		ft_putstr_fd("\n", node->redirection->heredoc_fd[1]);
	}
	free(heredoc->line);
}

void	init_heredoc(t_heredoc *heredoc)
{
	heredoc->current_delimiter = 0;
	heredoc->line = NULL;
	heredoc->is_expend = 1;
}
