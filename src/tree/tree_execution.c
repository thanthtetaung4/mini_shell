#include "../../header/minishell.h"
#include <sys/wait.h>

int init_pids(t_minishell *data)
{
	int num_of_pids;

	num_of_pids = 0;
	if (data->forking->heredoc_count != 0 || data->forking->redirection_count != 0 || data->forking->pipe_count != 0)
		num_of_pids = data->forking->pipe_count + data->forking->heredoc_count + data->forking->redirection_count;
	else if (data->forking->heredoc_count == 0 && data->forking->redirection_count == 0 && data->forking->pipe_count != 0)
		num_of_pids = data->forking->pipe_count + 1;
	data->forking->pids = malloc(sizeof(int) * (num_of_pids));
	if (!data->forking->pids)
		return (-1);
	return (num_of_pids);
}

void init_fds(t_minishell *data)
{
	int fds_count;
	int i;

	i = 0;
	if (data->forking->pipe_count > 0 || data->forking->heredoc_count > 0) 
	{
		fds_count = data->forking->pipe_count + data->forking->heredoc_count;
		data->forking->fds = malloc(sizeof(int *) * fds_count);
		while (i < fds_count)
		{
			data->forking->fds[i] = malloc(sizeof(int) * 2);
			i++;
		}
		if (!data->forking->fds) 
			return;
	} 
	else 
		data->forking->fds = NULL;
	if (data->forking->redirection_count > 0) 
	{
		data->forking->redirection_fds = malloc(sizeof(int) * data->forking->redirection_count);
		if (!data->forking->redirection_fds)
			return;
	} 
	else
		data->forking->redirection_fds = NULL;
}
int check_cmd(char *cmd)
{
	char *bultins[8];
	int i;

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
		if (strcmp(bultins[i], cmd) == 0)
			return (1);
		i++;
	}
	return (0);
}
int execute_command(t_minishell *data, t_ast_node *node, int i_pid)
{
	int *pids;
	int i;

	pids = data->forking->pids;
	char *args[256];

	pids[i_pid] = fork();
	if (pids[i_pid] == -1)
	{
		perror("fork");
		return (-1);
	}
	else if (pids[i_pid] == 0)
	{
		if (check_cmd(node->command[0]) == 1)
			ft_exec(data);
		else 
		{
			args[0] = ft_strjoin("/bin/", node->command[0]);
			i = 1;
			while (node->command[i]) {
				args[i] = node->command[i];
				i++;
			}
			args[i] = NULL;
			execve(args[0], args, NULL);
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(NULL);
	return (0);
}
int tree_execution(t_ast_node *lowest_node, t_minishell *data)
{
    t_ast_node *node;
    int i_pid = 0;
    int status;
	int num_pids;

	node = lowest_node;
    num_pids = init_pids(data); // Ensure you have the number of pids.
    while (node)
    {
        if (node->type == COMMAND)
        {
            if (node->parent && node->parent->type == PIPE)
            {
                // Handle pipes here
            }
            else if (!node->parent)
            {
                execute_command(data, node, i_pid);
                i_pid++;
            }
        }
        node = node->parent;
    }
    return data->status;
}
