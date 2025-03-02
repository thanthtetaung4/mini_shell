#include "../../header/minishell.h"

int extern g_sig_status;

void    free_heredoc(char *line, char **delimiters)
{
    int i;

    i = 0;
    free(line);
    while (delimiters[i])
    {
        free(delimiters[i]);
        i++;
    }
    free(delimiters);
}

// int heredoc(t_minishell *data, t_ast_node *node, int inside_pipe)
// {
//     char *line;
//     char **delimiters;
//     int i;
//     int j;

//     i = 0;
//     j = 0;
//     line = NULL;
//     delimiters = NULL;
//     delimiters = malloc(sizeof(char *) * (node->redirection->heredoc_count + 1));
//     while (node->redirection->types[i] && node->redirection->files[i])
//     {
//         if (node->redirection->types[i] == HEREDOC)
//         {
//             delimiters[j] = ft_strdup(node->redirection->files[i]);
//             j++;
//         }
//         i++;
//     }
//     delimiters[j] = NULL;
//     i = 0;
//     if (pipe(node->redirection->heredoc_fd) == -1)
//     {
//         perror("pipe");
//         return (EXIT_FAILURE);
//     }
//     g_sig_status = 0;
//     // signal(SIGINT,handle_heredoc_sigint);
//     set_signals_heredoc();
//     while (1)
//     {
//         if (g_sig_status == 1)
//         {
//             free_heredoc(line, delimiters);
//             break;
//         }
//         line = readline("> ");
//         if (!line)
//         {
//             free_heredoc(line, delimiters);
//             break;
//         }
//         if (ft_strcmp(line, delimiters[i]) == 0)
//         {
//             free(delimiters[i]);
//             i++;
//             if (i == node->redirection->heredoc_count)
//             {
//                 free(delimiters);
//                 free(line);
//                 break;
//             }
//         }
//         else if ((i ==( node->redirection->heredoc_count - 1)) && ft_strcmp(line, delimiters[i]) != 0 && node->command[0])
//         {
//             ft_putstr_fd(line, node->redirection->heredoc_fd[1]);
//             ft_putstr_fd("\n", node->redirection->heredoc_fd[1]);
//             // free(line);
//         }
//         free(line);
//     }
//     close(node->redirection->heredoc_fd[1]);
//     signal(SIGINT, handle_sigint);
//     return (g_sig_status);
// }

static char	**get_heredoc_delimiters(t_ast_node *node)
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

static int	setup_heredoc_pipe(t_ast_node *node)
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

static int	process_delimiter_match(char *line, char **delimiters,
		int *current_delimiter, int heredoc_count)
{
	if (ft_strcmp(line, delimiters[*current_delimiter]) == 0)
	{
		free(delimiters[*current_delimiter]);
		(*current_delimiter)++;
		if (*current_delimiter == heredoc_count)
		{
			return (1); // All delimiters processed
		}
	}
	return (0); // Continue processing
}

static void	write_to_heredoc(char *line, t_ast_node *node,
		int current_delimiter)
{
	if ((current_delimiter == (node->redirection->heredoc_count - 1))
		&& ft_strcmp(line, node->redirection->files[current_delimiter]) != 0
		&& node->command[0])
	{
		ft_putstr_fd(line, node->redirection->heredoc_fd[1]);
		ft_putstr_fd("\n", node->redirection->heredoc_fd[1]);
	}
}

static int	read_heredoc_input(t_ast_node *node, char **delimiters)
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

int	heredoc(t_minishell *data, t_ast_node *node, int inside_pipe)
{
	char **delimiters;
	int result;

	(void)data;        // Unused parameter
	(void)inside_pipe; // Unused parameter

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
