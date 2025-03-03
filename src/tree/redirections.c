#include "../../header/minishell.h"

int extern	g_sig_status;

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

void	handle_heredoc_input(t_minishell *data, t_ast_node *node,
		t_heredoc *heredoc)
{
	while (1)
	{
		heredoc->line = readline("> ");
		if (g_sig_status == 1)
		{
			free_heredoc(heredoc->line, heredoc->delimiter);
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
	free_heredoc(NULL, heredoc->delimiter);
}

void	init_heredoc(t_heredoc *heredoc)
{
	heredoc->current_delimiter = 0;
	heredoc->line = NULL;
}

int	heredoc(t_minishell *data, t_ast_node *node, int inside_pipe)
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
