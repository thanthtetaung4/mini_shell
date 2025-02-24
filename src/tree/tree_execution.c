#include "../../header/minishell.h"
#include <sys/wait.h>

void	init_forking_data(t_minishell *data)
{
	data->forking = malloc(sizeof(t_forking));
	data->forking->pids = NULL;
	data->forking->pipe_count = 0;
	data->forking->fds = NULL;
	data->forking->redirection_count = 0;
	data->forking->redirection_fds = NULL;
	data->forking->heredoc_count = 0;
	data->forking->i_fd = 0;
	data->forking->i_pid = 0;
	data->forking->i_rfd = 0;
	data->forking->completed_piping = 0;
}

int	init_pids(t_minishell *data)
{
	int	num_of_pids;

	num_of_pids = 0;
	if (data->forking->pipe_count > 0)
		num_of_pids = data->forking->pipe_count + 1;
	data->forking->pids = malloc(sizeof(int) * (num_of_pids));
	if (!data->forking->pids)
		return (-1);
	// printf("nums of pids => %d\n", num_of_pids);
	// printf("nums of pipe counts => %d\n", data->forking->pipe_count);
	return (num_of_pids);
}
void	init_fds(t_minishell *data)
{
	int	fds_count;
	int	i;

	i = 0;
	if (data->forking->pipe_count > 0 || data->forking->heredoc_count > 0)
	{
		fds_count = data->forking->pipe_count + data->forking->heredoc_count
			+ 1;
		data->forking->fds = malloc(sizeof(int *) * fds_count);
		if (!data->forking->fds)
			return ;
		while (i < fds_count)
		{
			data->forking->fds[i] = malloc(sizeof(int) * 2);
			i++;
		}
	}
	else
		data->forking->fds = NULL;
	if (data->forking->redirection_count > 0)
		data->forking->redirection_fds = malloc(sizeof(int)
				* data->forking->redirection_count);
	else
		data->forking->redirection_fds = NULL;
}

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
		if (strcmp(bultins[i], cmd) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	execute_command(t_minishell *data, t_ast_node *node)
{
	int		i;
	char	**args;
	char	**env_strings;
	struct stat path_stat;
	int		exit_status;

	if (data->args_count == 0 || ft_strlen(node->command[0]) == 0)
		return (0);
	args = malloc(sizeof(char *) * (data->args_count + 1));
	if (check_cmd(node->command[0]) == 1)
		return (ft_exec(data, node));
	else
	{
		args[0] = node->command[0];
		if (args[0][0] == '.' && args[0][1] == '/')
		{
			if (stat(args[0], &path_stat) == 0)
			{
				if (S_ISDIR(path_stat.st_mode))
				{
					ft_putstr_fd(" Is a directory\n", 2);
					free_2d_string(args);
					exit (126);
				}
			}
			if (access(args[0], F_OK) != 0)
			{
				ft_putstr_fd(" No such file or directory\n", 2);
				free_2d_string(args);
				exit (127);
			}
			if (access(args[0], X_OK) != 0)
			{
				ft_putstr_fd(" Permission denied\n", 2);
				free_2d_string(args);
				exit (126);
			}
		}
		if (args[0][0] == '/')
		{
			if (stat(args[0], &path_stat) == 0)
			{
				if (S_ISDIR(path_stat.st_mode))
				{
					ft_putstr_fd(" Is a directory\n", 2);
					free_2d_string(args);
					exit (126);
				}
			}
			if (access(args[0], F_OK) != 0)
			{
				ft_putstr_fd(" No such file or directory\n", 2);
				free_2d_string(args);
				exit (127);
			}
		}
		if ((node->command[0][0] != '.' && node->command[0][1] != '/')
		&& ft_strncmp(node->command[0], "/bin/", 5) != 0)
			args[0] = ft_strjoin("/bin/", node->command[0]);

		i = 1;
		while (i < data->args_count)
		{
			args[i] = ft_strdup(node->command[i]);
			i++;
		}
		args[i] = NULL;
		env_strings = get_env_strings(data->env);
		exit_status = execve(args[0], args, env_strings);
		if (exit_status == -1)
		{
				ft_putstr_fd(" command not found\n", 2);
				free_2d_string(args);
				free_cmd(&env_strings);
				exit (127);
		}
		free_cmd(&env_strings);
		exit(exit_status);
	}
	free_2d_string(args);
	exit(EXIT_SUCCESS);
	return (1);
}

int	execute_redirection(t_ast_node *node, t_minishell *data)
{
	int i;

	i = 0;
	while (node->redirection->types[i] != -1 && node->redirection->files[i] != NULL)
	{
		if (access(node->redirection->files[i], F_OK) == 0)
		{
			if (node->redirection->types[i] == OUTPUT || node->redirection->types[i] == APPEND)
			{
				if (access(node->redirection->files[i], W_OK) == 0 && access(node->redirection->files[i], R_OK) == 0)
				{
					if (node->redirection->types[i] == OUTPUT)
						data->forking->redirection_fds[i] = open(node->redirection->files[i],
								O_WRONLY | O_CREAT | O_TRUNC, 0644);
					else if (node->redirection->types[i] == APPEND)
						data->forking->redirection_fds[i] = open(node->redirection->files[i],
								O_WRONLY | O_CREAT | O_APPEND, 0644);
					if (data->forking->redirection_fds[i] == -1)
					{
						perror("open output file");
						return (1);
					}
					dup2(data->forking->redirection_fds[i], STDOUT_FILENO);
					close(data->forking->redirection_fds[i]);
				}
				else
				{
					ft_putstr_fd(node->redirection->files[i], 2);
					ft_putstr_fd(": Permission denied\n", 2);
					// printf("%s denied permission\n", node->file);
					return (1);
				}
			}
			else if (node->redirection->types[i] == INPUT)
			{
				if (access(node->redirection->files[i], R_OK) == 0)
				{
					data->forking->redirection_fds[i] = open(node->redirection->files[i], O_RDONLY);
					if (data->forking->redirection_fds[i] == -1)
					{
						perror("Error opening input file");
						exit(EXIT_FAILURE);
					}
					dup2(data->forking->redirection_fds[i], STDIN_FILENO);
					close(data->forking->redirection_fds[i]);
				}
				else
				{
					ft_putstr_fd(node->redirection->files[i], 2);
					ft_putstr_fd(": Permission denied\n", 2);
					// printf("%s denied permission\n", node->file);
					return (1);
				}
			}
			else if (node->redirection->types[i] == HEREDOC)
			{
				heredoc(data, node);
			}
		}
		else
		{
			if (node->redirection->types[i] == OUTPUT || node->redirection->types[i] == APPEND)
			{

					if (node->redirection->types[i] == OUTPUT)
						data->forking->output_fd = open(node->redirection->files[i],
								O_WRONLY | O_CREAT | O_TRUNC, 0644);
					else if (node->redirection->types[i] == APPEND)
						data->forking->output_fd = open(node->redirection->files[i],
								O_WRONLY | O_CREAT | O_APPEND, 0644);
					if (data->forking->output_fd == -1)
					{
						perror("open output file");
						return (1);
					}
					dup2(data->forking->output_fd, STDOUT_FILENO);
					close(data->forking->output_fd);

			}
			else if (node->redirection->types[i] == INPUT)
			{

					data->forking->input_fd = open(node->redirection->files[i], O_RDONLY);
					if (data->forking->input_fd == -1)
					{
						perror("Error opening input file");
						exit(EXIT_FAILURE);
					}
					dup2(data->forking->input_fd, STDIN_FILENO);
					close(data->forking->input_fd);

			}
			else if (node->redirection->types[i] == HEREDOC)
			{
				heredoc(data, node);
			}
		}
		i++;
	}
	return (0);
}

int	execute_single_command(t_minishell *data, t_ast_node *node)
{
	int		pid;
	int		i;
	int		exit_status;
	int		sig;
	int		stdout_fd;
	int		stdin_fd;

	stdout_fd = -1;
	stdin_fd = -1;
	exit_status = 0;
	i = 0;
	// printf("type: %d\n",node->redirection->types[0]);
	// printf("args count: %d\n", data->args_count);
	if (check_cmd(node->command[0]))
	{
		while (node->redirection->types[i] != -1 && node->redirection->files[i] != NULL)
		{
			if (node->redirection->types[i] == OUTPUT || node->redirection->types[i] == APPEND)
				stdout_fd = dup(STDOUT_FILENO);
			else if (node->redirection->types[i] == INPUT)
				stdin_fd = dup(STDIN_FILENO);
			i++;
		}
		if (node->redirection->types[0] != -1)
		{
			if (execute_redirection(node, data))
				return (1);
		}
		exit_status = ft_exec(data, node);
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
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return (-1);
		}
		else if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			if (node->redirection->types[0] != -1)
				if (execute_redirection(node, data))
					return (exit_status);
			exit_status = execute_command(data, node);
		}
		else
		{
			wait(&exit_status);
			if (WIFSIGNALED(exit_status))
			{
				sig = WTERMSIG(exit_status);
				if (sig == SIGQUIT)
				{
					write(1, "Quit: (Core dumped)\n", 20);
					exit_status = 128 + sig;
				}
				else if (sig == SIGINT)
				{
					write(1, "\n", 1);
					exit_status = 128 + sig;
				}
			}
			else if (WIFEXITED(exit_status))
			{
				exit_status = WEXITSTATUS(exit_status);
			}
		}
	}
	return (exit_status);
}

int	execute_pipe_command(t_minishell *data, t_ast_node *node)
{
	int		pid;
	int		i;
	char	*args[256];
	int		**fds;
	int		exit_status;
	int		sig;

	i = 0;
	fds = data->forking->fds;
	exit_status = 0;
	// init_pids(data);
	data->args_count = ft_count_tds(node->command);
	if (pipe(data->forking->fds[data->forking->i_fd]) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (data->forking->completed_piping > 0)
			dup2(data->forking->fds[data->forking->i_fd - 1][0], STDIN_FILENO);
		if (data->forking->completed_piping < data->forking->pipe_count)
			dup2(data->forking->fds[data->forking->i_fd][1], STDOUT_FILENO);
		while (i <= data->forking->i_fd)
		{
			close(data->forking->fds[i][0]);
			close(data->forking->fds[i][1]);
			i++;
		}
		if (node->redirection->types[0] != -1)
			if (execute_redirection(node, data))
				exit(1);
		exit_status = execute_command(data, node);
		free_all(data, 1);
	}
	else
	{
		data->forking->completed_piping++;
		close(data->forking->fds[data->forking->i_fd][1]);
		// close(data->forking->fds[data->forking->i_fd][0]);
		data->forking->pids[data->forking->i_pid] = pid;
		data->forking->i_pid++;
		if (data->forking->i_fd > 0)
		{
			close(data->forking->fds[data->forking->i_fd - 1][0]);
		}
	}
	return (exit_status);
}

int	tree_execution(t_ast_node *lowest_node, t_minishell *data)
{
	t_ast_node	*node;
	t_ast_node	*temp_node;
	int			status;
	int			i;
	int			exit_status;
	int			sig;

	exit_status = 0;
	node = lowest_node;
	init_fds(data);
	init_pids(data);
	while (node)
	{
		if (node->type == COMMAND)
		{
			if (node->parent && node->parent->type == PIPE)
			{
				data->status = execute_pipe_command(data, node);
				data->forking->i_fd++;
			}
			else if (!node->parent)
			{
				data->status = execute_single_command(data, node);
			}
		}
		else if (node->type == PIPE)
		{
			temp_node = node->right;
			data->status = execute_pipe_command(data, temp_node);
			data->forking->i_fd++;
		}
		node = node->parent;
	}
	i = 0;
	while (i < data->forking->completed_piping)
	{
		// wait(&data->status);
		// printf("pid %d => %d\n",i,data->forking->pids[i]);
		waitpid(data->forking->pids[i], &data->status, 0);
		i++;
	}
	if (data->forking->pipe_count == 0)
	{
		if (WIFSIGNALED(data->status))
		{
			sig = WTERMSIG(data->status);
			if (sig == SIGQUIT)
			{
				write(1, "Quit: (Core dumped)\n", 20);
				data->status = 128 + sig;
			}
			else if (sig == SIGINT)
			{
				write(1, "\n", 1);
				data->status = 128 + sig;
			}
		}
		else if (WIFEXITED(data->status))
		{
			exit_status = WEXITSTATUS(data->status);
		}
	}
	else
	{
		if (WIFSIGNALED(data->status))
		{
			sig = WTERMSIG(data->status);
			if (sig == SIGINT)
				write(1, "\n", 1);
				data->status = 0;
		}
		else if (WIFEXITED(data->status))
		{
			data->status = WEXITSTATUS(data->status);
		}
	}
	//close(data->forking->fds[data->forking->i_fd - 2][1]);
	//close(data->forking->fds[data->forking->i_fd][1]);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	// printf("status: %d\n", data->status);
	return (data->status);
}
