#include "../../header/minishell.h"

int heredoc(t_minishell *data, t_ast_node *node)
{
    char *line;
    char **delimiters;
    int i;
    int j;

    i = 0;
    j = 0;
    line = NULL;
    delimiters = NULL;
    delimiters = malloc(sizeof(char *) * (node->redirection->heredoc_count + 1));
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
    i = 0;
    if (pipe(data->forking->fds[data->forking->i_fd]) == -1)
    {
        perror("pipe");
        return (EXIT_FAILURE);
    }
    while (1)
    {
        // printf("hc %d, i %d\n", node->redirection->heredoc_count, i);
        line = readline("> ");
        if (!line)
            break;
        if (ft_strcmp(line, delimiters[i]) == 0)
        {
            free(delimiters[i]);
            free(line);
            i++;
            if (i == node->redirection->heredoc_count)
            {
                free(delimiters);
                break;
            }
            else
            {
                close(data->forking->fds[data->forking->i_fd][1]);
                // dup2(data->forking->fds[data->forking->i_fd][0], STDIN_FILENO);
                close(data->forking->fds[data->forking->i_fd][0]);
                data->forking->i_fd++;
                if (pipe(data->forking->fds[data->forking->i_fd]) == -1)
                {
                    perror("pipe");
                    return (EXIT_FAILURE);
                }
            }
        }
        else
        {
            ft_putstr_fd(line, data->forking->fds[data->forking->i_fd][1]);
            ft_putstr_fd("\n", data->forking->fds[data->forking->i_fd][1]);
            free(line);
        }
    }
    close(data->forking->fds[data->forking->i_fd][1]);
    dup2(data->forking->fds[data->forking->i_fd][0], STDIN_FILENO);
    close(data->forking->fds[data->forking->i_fd][0]);
    return (0);
}

