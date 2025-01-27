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
		{
			perror("malloc failed for fds");
			return;
		}
	} 
	else 
		data->forking->fds = NULL;
	if (data->forking->redirection_count > 0) {
		data->forking->redirection_fds = malloc(sizeof(int) * data->forking->redirection_count);
		if (!data->forking->redirection_fds) {
			perror("malloc failed for redirection_fds");
			return;
		}
	} 
	else
		data->forking->redirection_fds = NULL;
}
int check_cmd(char *cmd)
{
	char *bultins[7];
	int i;

	i = 0;
    bultins[0] = "cd";
    bultins[1] = "echo";
    bultins[2] = "env";
    bultins[3] = "exit";
    bultins[4] = "pwd";
    bultins[5] = "unset";
    bultins[6] = NULL;
	while (bultins[i] != NULL)
	{
		if (strcmp(bultins[i], cmd) == 0)
			return (1);
		i++;
	}
	return (0);
}
int tree_execution(t_ast_node *lowest_node, t_minishell *data)
{
	t_ast_node *node;
	t_ast_node *temp_node;
	int i;
	int i_fd;
	int i_rfd;
	int i_pid;
	int **fds;
	int *rfds;
	char *args[256];
	int num_of_pid;

	//
	i = 0;
	i_fd = 0;
	i_rfd = 0;
	i_pid = 0;
	num_of_pid = init_pids(data);
	init_fds(data);
	fds = data->forking->fds;
	rfds = data->forking->redirection_fds;
	node = lowest_node;
	temp_node = NULL;
	while (node)
	{
		if (node->type == COMMAND)
		{
			if (node->parent)
			{
				if (node->parent && node->parent->type == PIPE && fds != NULL) 
				{
					if (fds && pipe(fds[i_fd]) == -1) 
					{
    					perror("pipe");
    					exit(1);
					}
					if (!fds) {
						fprintf(stderr, "Error: fds is not initialized\n");
						exit(1);
					}
					data->forking->pids[i_pid] = fork();
					if (data->forking->pids[i_pid] == -1) {
						perror("fork");
						exit(1);
					}
					if (data->forking->pids[i_pid] == 0) 
					{ // Child process
						dup2(fds[i_fd][1], STDOUT_FILENO); // Redirect stdout to pipe write end
						close(fds[i_fd][0]);            
						close(fds[i_fd][1]);
						if (check_cmd(node->command[0]) == 1)
							ft_exec(data);
						else {
							args[0] = ft_strjoin("/bin/", node->command[0]);
							i = 1;
							// args[0] ="hi";
							// printf("%s\n", args[0]);
							while (node->command[i]) {
								args[i] = node->command[i];
								i++;
							}
							args[i] =NULL;
							execve(args[0], args, NULL);
							perror("execve");
						}
						// printf("%s\n", args[0]);
						exit(1);
					}
					i_fd++;
					i_pid++;
				}
			}
			node->executed = 1;
			node = node->parent;
		}
		else if (node->type == PIPE)
		{
			temp_node = node->right;
			if (temp_node->executed == 0)
			{
				//
				data->forking->pids[i_pid] = fork();
				if (data->forking->pids[i_pid] == -1) 
				{
					perror("fork");
					exit(1);
				}
				if (data->forking->pids[i_pid] == 0) 
				{ // Child process
					dup2(fds[i_fd - 1][0], STDIN_FILENO);
					dup2(fds[i_fd][1], STDOUT_FILENO); // Redirect stdout to pipe write end
					close(fds[i_fd - 1][0]);            
					close(fds[i_fd - 1][1]);
					close(fds[i_fd][0]);            
					close(fds[i_fd][1]);
					if (check_cmd(temp_node->command[0]) == 1)
						ft_exec(data);
					else {
						args[0] = ft_strjoin("/bin/", temp_node->command[0]);
						i = 1;
						while (temp_node->command[i]) {
							args[i] = temp_node->command[i];
							i++;
						}
						args[i] =NULL;
						execve(args[0], args, NULL);
						perror("execve");
					}
					exit(1);
				}
				i_fd++;
				i_pid++;
				temp_node->executed = 1;
				node = node->parent;
			}
			else
				node = node->parent;
		}
	}
	i = 0;
	while (i < i_fd)
	{
		if (fds[i])
		{
			close(fds[i][0]);
			close(fds[i][1]);
		}
		i++;
	}
	i = 0;
	while (i < i_pid)
	{
		waitpid(data->forking->pids[i], NULL, 0);
		i++;
	}
	return (0);
}
