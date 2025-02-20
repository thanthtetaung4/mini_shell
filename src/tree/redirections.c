#include "../../header/minishell.h"

int heredoc(t_minishell *data, t_ast_node *node)
{
    char *line;

    if (pipe(data->forking->fds[data->forking->i_fd]) == -1)
    {
        perror("pipe");
        return (EXIT_FAILURE);
    }
    while (1)
    {
		line = readline("> ");
		if (!line)
            break;
        if (ft_strcmp(line, node->file) == 0)
        {
            free(line);
            break;
        }
        ft_putstr_fd(line, data->forking->fds[data->forking->i_fd][1]);
        ft_putstr_fd("\n", data->forking->fds[data->forking->i_fd][1]);
        free(line);
    }
    close(data->forking->fds[data->forking->i_fd][1]);
    dup2(data->forking->fds[data->forking->i_fd][0], STDIN_FILENO);
    close(data->forking->fds[data->forking->i_fd][0]);
    return (0);
}

