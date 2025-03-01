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

int heredoc(t_minishell *data, t_ast_node *node, int inside_pipe)
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
    if (pipe(node->redirection->heredoc_fd) == -1)
    {
        perror("pipe");
        return (EXIT_FAILURE);
    }
    g_sig_status = 0;
    // signal(SIGINT,handle_heredoc_sigint);
    set_signals_heredoc();
    while (1)
    {
        if (g_sig_status == 1)
        {
            free_heredoc(line, delimiters);
            break;
        }
        line = readline("> ");
        if (g_sig_status == 1)
        {
            free_heredoc(line, delimiters);
            break;
        }
        if (!line)
            break;
        if (ft_strcmp(line, delimiters[i]) == 0)
        {
            free(delimiters[i]);
            i++;
            if (i == node->redirection->heredoc_count)
            {
                free(delimiters);
                free(line);
                break;
            }
        }
        else if ((i ==( node->redirection->heredoc_count - 1)) && ft_strcmp(line, delimiters[i]) != 0 && node->command[0])
        {
            ft_putstr_fd(line, node->redirection->heredoc_fd[1]);
            ft_putstr_fd("\n", node->redirection->heredoc_fd[1]);
            // free(line);
        }
        free(line);
    }
    close(node->redirection->heredoc_fd[1]);
    signal(SIGINT, handle_sigint);
    return (g_sig_status);
}

