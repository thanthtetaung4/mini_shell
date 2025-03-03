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
	return (num_of_pids);
}
void	init_fds(t_minishell *data)
{
	int	fds_count;
	int	i;

	i = 0;
	if (data->forking->pipe_count > 0)
	{
		fds_count = data->forking->pipe_count + 1;
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
	int			i;
	char		**args;
	char		**env_strings;
	struct stat	path_stat;
	int			exit_status;

	if (data->args_count == 0 || ft_strlen(node->command[0]) == 0)
		return (0);
	if (check_cmd(node->command[0]) == 1)
	{
		exit_status = ft_exec(data, node);
		free_all(data, 1);
		exit(exit_status);
	}
	else if (data->forking->pipe_count == 0)
	{
		args = malloc(sizeof(char *) * (data->args_count + 1));
		if (node->command[0][0] == '.' && node->command[0][1] == '/')
		{
			if (stat(node->command[0], &path_stat) == 0)
			{
				if (S_ISDIR(path_stat.st_mode))
				{
					ft_putstr_fd(" Is a directory\n", 2);
					free(args);
					free_all(data, 1);
					exit(126);
				}
			}
			if (access(node->command[0], F_OK) != 0)
			{
				ft_putstr_fd(" No such file or directory\n", 2);
				free(args);
				free_all(data, 1);
				exit(127);
			}
			if (access(node->command[0], X_OK) != 0)
			{
				ft_putstr_fd(" Permission denied\n", 2);
				free(args);
				free_all(data, 1);
				exit(126);
			}
		}
		if (node->command[0][0] == '/')
		{
			if (stat(node->command[0], &path_stat) == 0)
			{
				if (S_ISDIR(path_stat.st_mode))
				{
					ft_putstr_fd(" Is a directory\n", 2);
					free(args);
					free_all(data, 1);
					exit(126);
				}
			}
			if (access(node->command[0], F_OK) != 0)
			{
				ft_putstr_fd(" No such file or directory\n", 2);
				free(args);
				free_all(data, 1);
				exit(127);
			}
		}
		args[0] = ft_strdup(node->command[0]);
		if ((node->command[0][0] != '.' && node->command[0][1] != '/')
			&& ft_strncmp(node->command[0], "/bin/", 5) != 0)
		{
			args[0] = find_command_path(args[0], data);
		}
		i = 1;
		while (node->command[i])
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
			free_all(data, 1);
			exit(127);
		}
		free_cmd(&env_strings);
		free_2d_string(args);
		free_all(data, 1);
		exit(exit_status);
	}
	else if (data->forking->pipe_count > 0)
	{
		args = malloc(sizeof(char *) * (data->args_count + 1));
		if (node->command[0][0] == '.' && node->command[0][1] == '/')
		{
			if (stat(node->command[0], &path_stat) == 0)
			{
				if (S_ISDIR(path_stat.st_mode))
				{
					ft_putstr_fd(" Is a directory\n", 2);
					free(args);
					free_all(data, 1);
					exit(126);
				}
			}
			if (access(node->command[0], F_OK) != 0)
			{
				ft_putstr_fd(" No such file or directory\n", 2);
				free(args);
				free_all(data, 1);
				exit(127);
			}
			if (access(node->command[0], X_OK) != 0)
			{
				ft_putstr_fd(" Permission denied\n", 2);
				free(args);
				free_all(data, 1);
				exit(126);
			}
		}
		if (node->command[0][0] == '/')
		{
			if (stat(node->command[0], &path_stat) == 0)
			{
				if (S_ISDIR(path_stat.st_mode))
				{
					ft_putstr_fd(" Is a directory\n", 2);
					free(args);
					free_all(data, 1);
					exit(126);
				}
			}
			if (access(node->command[0], F_OK) != 0)
			{
				ft_putstr_fd(" No such file or directory\n", 2);
				free(args);
				free_all(data, 1);
				exit(127);
			}
		}

		if ((node->command[0][0] != '.' && node->command[0][1] != '/')
			&& ft_strncmp(node->command[0], "/bin/", 5) != 0)
		{
			args[0] = find_command_path(node->command[0], data);
		}
		else
			args[0] = ft_strdup(node->command[0]);
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
			free_all(data, 1);
			exit(127);
		}
		free_cmd(&env_strings);
		free_2d_string(args);
		exit(exit_status);
	}
	return (1);
}

// int	execute_redirection(t_ast_node *node, t_minishell *data)
// {
// 	int i;
// 	int pid;

// 	i = 0;
// 	while (node->redirection->types[i] != -1
// && node->redirection->files[i] != NULL)
// 	{
// 		if (access(node->redirection->files[i], F_OK) == 0)
// 		{
// 			if (node->redirection->types[i] == OUTPUT
// || node->redirection->types[i] == APPEND)
// 			{
// 				if (access(node->redirection->files[i], W_OK) == 0
// && access(node->redirection->files[i], R_OK) == 0)
// 				{
// 					if (node->redirection->types[i] == OUTPUT)
// 						data->forking->redirection_fds[i] = open(node->redirection->files[i],
// 								O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 					else if (node->redirection->types[i] == APPEND)
// 						data->forking->redirection_fds[i] = open(node->redirection->files[i],
// 								O_WRONLY | O_CREAT | O_APPEND, 0644);
// 					if (data->forking->redirection_fds[i] == -1)
// 					{
// 						perror("open output file");
// 						return (EXIT_FAILURE);
// 					}
// 					dup2(data->forking->redirection_fds[i], STDOUT_FILENO);
// 					close(data->forking->redirection_fds[i]);
// 				}
// 				else
// 				{
// 					ft_putstr_fd(node->redirection->files[i], 2);
// 					ft_putstr_fd(": Permission denied\n", 2);
// 					return(EXIT_FAILURE);
// 				}
// 			}
// 			else if (node->redirection->types[i] == INPUT)
// 			{
// 				if (access(node->redirection->files[i], R_OK) == 0)
// 				{
// 					data->forking->redirection_fds[i] = open(node->redirection->files[i],
// O_RDONLY);
// 					if (data->forking->redirection_fds[i] == -1)
// 					{
// 						perror("Error opening input file");
// 						return(EXIT_FAILURE);
// 					}
// 					dup2(data->forking->redirection_fds[i], STDIN_FILENO);
// 					close(data->forking->redirection_fds[i]);
// 				}
// 				else
// 				{
// 					ft_putstr_fd(node->redirection->files[i], 2);
// 					ft_putstr_fd(": Permission denied\n", 2);
// 					return(EXIT_FAILURE);
// 				}
// 			}
// 			else if (node->redirection->types[i] == HEREDOC)
// 			{
// 				dup2(node->redirection->heredoc_fd[0], STDIN_FILENO);
// 				close(node->redirection->heredoc_fd[0]);
// 				if (!node->redirection->types[i + 1])
// 					break ;
// 			}
// 		}
// 		else
// 		{
// 			if (node->redirection->types[i] == OUTPUT
// || node->redirection->types[i] == APPEND)
// 			{
// 					if (node->redirection->types[i] == OUTPUT)
// 						data->forking->redirection_fds[i] = open(node->redirection->files[i],
// 								O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 					else if (node->redirection->types[i] == APPEND)
// 						data->forking->redirection_fds[i] = open(node->redirection->files[i],
// 								O_WRONLY | O_CREAT | O_APPEND, 0644);
// 					if (data->forking->redirection_fds[i] == -1)
// 					{
// 						ft_putstr_fd("cannot open output file\n",2);
// 						return(EXIT_FAILURE);
// 					}
// 					dup2(data->forking->redirection_fds[i], STDOUT_FILENO);
// 					close(data->forking->redirection_fds[i]);
// 			}
// 			else if (node->redirection->types[i] == INPUT)
// 			{
// 				data->forking->redirection_fds[i] = open(node->redirection->files[i],
// O_RDONLY);
// 					if (data->forking->redirection_fds[i] == -1)
// 					{
// 						perror("Error opening input file");
// 						return(EXIT_FAILURE);
// 					}
// 					dup2(data->forking->redirection_fds[i], STDIN_FILENO);
// 					close(data->forking->redirection_fds[i]);
// 			}
// 			else if (node->redirection->types[i] == HEREDOC)
// 			{
// 				dup2(node->redirection->heredoc_fd[0], STDIN_FILENO);
// 				close(node->redirection->heredoc_fd[0]);
// 				if (!node->redirection->types[i + 1])
// 					break ;
// 			}
// 		}
// 		i++;
// 	}
// 	return (0);
// }

static int	handle_output_redirection(t_ast_node *node, t_minishell *data,
		int i)
{
	int	file_fd;

	if (node->redirection->types[i] == OUTPUT)
		file_fd = open(node->redirection->files[i],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		file_fd = open(node->redirection->files[i],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (file_fd == -1)
	{
		ft_putstr_fd("cannot open output file\n", 2);
		return (EXIT_FAILURE);
	}
	data->forking->redirection_fds[i] = file_fd;
	dup2(file_fd, STDOUT_FILENO);
	close(file_fd);
	return (0);
}

static int	handle_input_redirection(t_ast_node *node, t_minishell *data, int i)
{
	int	file_fd;

	file_fd = open(node->redirection->files[i], O_RDONLY);
	if (file_fd == -1)
	{
		perror("Error opening input file");
		return (EXIT_FAILURE);
	}
	data->forking->redirection_fds[i] = file_fd;
	dup2(file_fd, STDIN_FILENO);
	close(file_fd);
	return (0);
}

static int	handle_heredoc_redirection(t_ast_node *node)
{
	dup2(node->redirection->heredoc_fd[0], STDIN_FILENO);
	close(node->redirection->heredoc_fd[0]);
	return (0);
}

static int	handle_existing_file_redirection(t_ast_node *node,
		t_minishell *data, int i)
{
	if (node->redirection->types[i] == OUTPUT
		|| node->redirection->types[i] == APPEND)
	{
		if (access(node->redirection->files[i], W_OK) == 0
			&& access(node->redirection->files[i], R_OK) == 0)
			return (handle_output_redirection(node, data, i));
		else
		{
			ft_putstr_fd(node->redirection->files[i], 2);
			ft_putstr_fd(": Permission denied\n", 2);
			return (EXIT_FAILURE);
		}
	}
	else if (node->redirection->types[i] == INPUT)
	{
		if (access(node->redirection->files[i], R_OK) == 0)
			return (handle_input_redirection(node, data, i));
		else
		{
			ft_putstr_fd(node->redirection->files[i], 2);
			ft_putstr_fd(": Permission denied\n", 2);
			return (EXIT_FAILURE);
		}
	}
	return (0);
}

static int	handle_new_file_redirection(t_ast_node *node, t_minishell *data,
		int i)
{
	if (node->redirection->types[i] == OUTPUT
		|| node->redirection->types[i] == APPEND)
	{
		return (handle_output_redirection(node, data, i));
	}
	else if (node->redirection->types[i] == INPUT)
	{
		return (handle_input_redirection(node, data, i));
	}
	return (0);
}

// int	execute_redirection(t_ast_node *node, t_minishell *data)
// {
// 	int	i;
// 	int	result;

// 	i = 0;
// 	while (node->redirection->types[i] != -1
// 		&& node->redirection->files[i] != NULL)
// 	{
// 		if (node->redirection->types[i] == HEREDOC)
// 		{
// 			result = handle_heredoc_redirection(node);
// 			if (!node->redirection->types[i + 1])
// 				break ;
// 		}
// 		else if (access(node->redirection->files[i], F_OK) == 0)
// 		{
// 			result = handle_existing_file_redirection(node, data, i);
// 			if (result != 0)
// 				return (result);
// 		}
// 		else
// 		{
// 			result = handle_new_file_redirection(node, data, i);
// 			if (result != 0)
// 				return (result);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

int	handle_heredoc_if_needed(t_ast_node *node, int i)
{
	int	result;

	if (node->redirection->types[i] == HEREDOC)
	{
		result = handle_heredoc_redirection(node);
		if (!node->redirection->types[i + 1])
			return (-1);
	}
	return (0);
}

int	process_file_redirection(t_ast_node *node, t_minishell *data, int i)
{
	int	result;

	if (access(node->redirection->files[i], F_OK) == 0)
		result = handle_existing_file_redirection(node, data, i);
	else
		result = handle_new_file_redirection(node, data, i);
	return (result);
}

int	execute_redirection(t_ast_node *node, t_minishell *data)
{
	int	i;
	int	result;

	i = 0;
	while (node->redirection->types[i] != -1
		&& node->redirection->files[i] != NULL)
	{
		if (handle_heredoc_if_needed(node, i) == -1)
			break ;
		result = process_file_redirection(node, data, i);
		if (result != 0)
			return (result);
		i++;
	}
	return (0);
}

// int	execute_single_command(t_minishell *data, t_ast_node *node)
// {
// 	int	pid;
// 	int	i;
// 	int	exit_status;
// 	int	sig;
// 	int	stdout_fd;
// 	int	stdin_fd;

// 	stdout_fd = -1;
// 	stdin_fd = -1;
// 	exit_status = 0;
// 	i = 0;
// 	if (!node->command[0])
// 	{
// 		close(node->redirection->heredoc_fd[0]);
// 		return (0);
// 	}
// 	if (node->command[0] && check_cmd(node->command[0]))
// 	{
// 		while (node->redirection->types[i] != -1
// 			&& node->redirection->files[i] != NULL)
// 		{
// 			if (node->redirection->types[i] == OUTPUT
// 				|| node->redirection->types[i] == APPEND)
// 			{
// 				if (stdout_fd != -1)
// 				{
// 					close(stdout_fd);
// 				}
// 				stdout_fd = dup(STDOUT_FILENO);
// 			}
// 			else if (node->redirection->types[i] == INPUT
// 				|| node->redirection->types[i] == HEREDOC)
// 			{
// 				if (stdin_fd != -1)
// 				{
// 					close(stdin_fd);
// 				}
// 				stdin_fd = dup(STDIN_FILENO);
// 			}
// 			i++;
// 		}
// 		if (node->redirection->types[0] != -1)
// 		{
// 			if (execute_redirection(node, data))
// 			{
// 				// free_all(data, 1);
// 				// reset_forking_data(data);
// 				dup2(stdout_fd, STDOUT_FILENO);
// 				dup2(stdin_fd, STDIN_FILENO);
// 				close(stdout_fd);
// 				close(stdin_fd);
// 				return (1);
// 			}
// 		}
// 		exit_status = ft_exec(data, node);
// 		if (stdout_fd != -1)
// 		{
// 			dup2(stdout_fd, STDOUT_FILENO);
// 			close(stdout_fd);
// 		}
// 		if (stdin_fd != -1)
// 		{
// 			dup2(stdin_fd, STDIN_FILENO);
// 			close(stdin_fd);
// 		}
// 	}
// 	else
// 	{
// 		signal(SIGINT, SIG_IGN);
// 		signal(SIGQUIT, SIG_IGN);
// 		pid = fork();
// 		if (pid == -1)
// 		{
// 			perror("fork");
// 			return (-1);
// 		}
// 		else if (pid == 0)
// 		{
// 			signal(SIGINT, SIG_DFL);
// 			signal(SIGQUIT, SIG_DFL);
// 			if (node->redirection->types[0] != -1)
// 				if (execute_redirection(node, data))
// 				{
// 					free_all(data, 1);
// 					exit(1);
// 				}
// 			exit_status = execute_command(data, node);
// 		}
// 		else
// 		{
// 			waitpid(pid, &exit_status, 0);
// 			if (WIFSIGNALED(exit_status))
// 			{
// 				sig = WTERMSIG(exit_status);
// 				if (sig == SIGQUIT)
// 				{
// 					write(1, "Quit: (Core dumped)\n", 20);
// 					exit_status = 128 + sig;
// 				}
// 				else if (sig == SIGINT)
// 				{
// 					write(1, "\n", 1);
// 					exit_status = 128 + sig;
// 				}
// 			}
// 			else if (WIFEXITED(exit_status))
// 			{
// 				exit_status = WEXITSTATUS(exit_status);
// 			}
// 		}
// 	}
// 	if (node->redirection->heredoc_count > 0)
// 		close(node->redirection->heredoc_fd[0]);
// 	return (exit_status);
// }

static void	save_std_fds(t_ast_node *node, int *stdout_fd, int *stdin_fd)
{
	int	i;

	i = 0;
	*stdout_fd = -1;
	*stdin_fd = -1;
	while (node->redirection->types[i] != -1
		&& node->redirection->files[i] != NULL)
	{
		if (node->redirection->types[i] == OUTPUT
			|| node->redirection->types[i] == APPEND)
		{
			if (*stdout_fd != -1)
				close(*stdout_fd);
			*stdout_fd = dup(STDOUT_FILENO);
		}
		else if (node->redirection->types[i] == INPUT
			|| node->redirection->types[i] == HEREDOC)
		{
			if (*stdin_fd != -1)
				close(*stdin_fd);
			*stdin_fd = dup(STDIN_FILENO);
		}
		i++;
	}
}

static void	restore_std_fds(int stdout_fd, int stdin_fd)
{
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

static int	execute_builtin_with_redirections(t_minishell *data,
		t_ast_node *node, int stdout_fd, int stdin_fd)
{
	int	exit_status;

	exit_status = 0;
	if (node->redirection->types[0] != -1)
	{
		if (execute_redirection(node, data))
		{
			restore_std_fds(stdout_fd, stdin_fd);
			return (1);
		}
	}
	exit_status = ft_exec(data, node);
	restore_std_fds(stdout_fd, stdin_fd);
	return (exit_status);
}

static void	setup_child_process(t_minishell *data, t_ast_node *node)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (node->redirection->types[0] != -1)
	{
		if (execute_redirection(node, data))
		{
			free_all(data, 1);
			exit(1);
		}
	}
	execute_command(data, node);
}

static int	handle_child_exit_status(int exit_status)
{
	int	sig;

	if (WIFSIGNALED(exit_status))
	{
		sig = WTERMSIG(exit_status);
		if (sig == SIGQUIT)
		{
			write(1, "Quit: (Core dumped)\n", 20);
			return (128 + sig);
		}
		else if (sig == SIGINT)
		{
			write(1, "\n", 1);
			return (128 + sig);
		}
	}
	else if (WIFEXITED(exit_status))
	{
		return (WEXITSTATUS(exit_status));
	}
	return (exit_status);
}

static int	execute_external_cmd(t_minishell *data, t_ast_node *node)
{
	int	pid;
	int	exit_status;

	exit_status = 0;
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
		setup_child_process(data, node);
	}
	else
	{
		waitpid(pid, &exit_status, 0);
		exit_status = handle_child_exit_status(exit_status);
	}
	return (exit_status);
}

int	execute_single_command(t_minishell *data, t_ast_node *node)
{
	int	stdout_fd;
	int	stdin_fd;
	int	exit_status;

	stdout_fd = -1;
	stdin_fd = -1;
	exit_status = 0;
	if (!node->command[0])
	{
		close(node->redirection->heredoc_fd[0]);
		return (0);
	}
	if (node->command[0] && check_cmd(node->command[0]))
	{
		save_std_fds(node, &stdout_fd, &stdin_fd);
		exit_status = execute_builtin_with_redirections(data, node, stdout_fd,
				stdin_fd);
	}
	else
	{
		exit_status = execute_external_cmd(data, node);
	}
	if (node->redirection->heredoc_count > 0)
		close(node->redirection->heredoc_fd[0]);
	return (exit_status);
}

void	close_heredoc_fds_c(t_minishell *data)
{
	t_ast_node	*temp_node;

	temp_node = data->tree->lowest_node;
	while (temp_node)
	{
		if (temp_node->type == COMMAND)
		{
			// if (temp_node->redirection->heredoc_fd[0] != -1)
			close(temp_node->redirection->heredoc_fd[0]);
			// if ( temp_node->redirection->heredoc_fd[1] != -1)
			close(temp_node->redirection->heredoc_fd[1]);
		}
		else if (temp_node->type == PIPE)
		{
			// if (temp_node->right->redirection->heredoc_fd[0] != -1)
			close(temp_node->right->redirection->heredoc_fd[0]);
			// if (temp_node->right->redirection->heredoc_fd[1] != -1)
			close(temp_node->right->redirection->heredoc_fd[1]);
		}
		temp_node = temp_node->parent;
	}
}
void	close_heredoc_fds_p(t_minishell *data)
{
	t_ast_node	*temp_node;

	temp_node = data->tree->lowest_node;
	while (temp_node)
	{
		if (temp_node->type == COMMAND)
		{
			if (temp_node->redirection->heredoc_fd[0] != -1)
				close(temp_node->redirection->heredoc_fd[0]);
			if (temp_node->redirection->heredoc_fd[1] != -1)
				close(temp_node->redirection->heredoc_fd[1]);
		}
		else if (temp_node->type == PIPE)
		{
			if (temp_node->right->redirection->heredoc_fd[0] != -1)
				close(temp_node->right->redirection->heredoc_fd[0]);
			if (temp_node->right->redirection->heredoc_fd[1] != -1)
				close(temp_node->right->redirection->heredoc_fd[1]);
		}
		temp_node = temp_node->parent;
	}
}

// int	execute_pipe_command(t_minishell *data, t_ast_node *node)
// {
// 	int	pid;
// 	int	i;
// 	int	exit_status;
// 	int	sig;

// 	i = 0;
// 	exit_status = 0;
// 	data->args_count = ft_count_tds(node->command);
// 	if (pipe(data->forking->fds[data->forking->i_fd]) == -1)
// 	{
// 		perror("pipe");
// 		exit(EXIT_FAILURE);
// 	}
// 	signal(SIGINT, SIG_IGN);
// 	signal(SIGQUIT, SIG_IGN);
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("fork");
// 		return (-1);
// 	}
// 	else if (pid == 0)
// 	{
// 		signal(SIGINT, SIG_DFL);
// 		signal(SIGQUIT, SIG_DFL);
// 		if (!node->command[0])
// 		{
// 			close(data->forking->fds[data->forking->i_fd][0]);
// 			close(data->forking->fds[data->forking->i_fd][1]);
// 			close_heredoc_fds_p(data);
// 			free_all(data, 1);
// 			exit(0);
// 		}
// 		if (data->forking->completed_piping > 0 && data->empty_prev_node == 0)
// 		{
// 			dup2(data->forking->fds[data->forking->i_fd - 1][0], STDIN_FILENO);
// 		}
// 		if (data->forking->completed_piping > 0 && data->empty_prev_node == 1)
// 		{
// 			if (data->forking->pipe_count > 1)
// 			{
// 				dup2(node->parent->left->right->redirection->heredoc_fd[0],
// 					STDIN_FILENO);
// 				close(node->parent->left->right->redirection->heredoc_fd[0]);
// 			}
// 			else if (data->forking->pipe_count == 1)
// 			{
// 				dup2(node->parent->left->redirection->heredoc_fd[0],
// 					STDIN_FILENO);
// 				close(node->parent->left->redirection->heredoc_fd[0]);
// 			}
// 		}
// 		if ((data->forking->completed_piping < data->forking->pipe_count))
// 		{
// 			dup2(data->forking->fds[data->forking->i_fd][1], STDOUT_FILENO);
// 		}
// 		while (i <= data->forking->i_fd)
// 		{
// 			close(data->forking->fds[i][0]);
// 			close(data->forking->fds[i][1]);
// 			i++;
// 		}
// 		if (node->redirection->types[0] != -1)
// 		{
// 			if (execute_redirection(node, data))
// 			{
// 				free_all(data, 1);
// 				exit(1);
// 			}
// 		}
// 		exit_status = execute_command(data, node);
// 		if (node->redirection->heredoc_count > 0)
// 			close_heredoc_fds_c(data);
// 		free_all(data, 1);
// 	}
// 	else
// 	{
// 		close(data->forking->fds[data->forking->i_fd][1]);
// 		if (!node->command[0]
// 			|| data->forking->completed_piping == data->forking->pipe_count)
// 			close(data->forking->fds[data->forking->i_fd][0]);
// 		data->forking->pids[data->forking->i_pid] = pid;
// 		data->forking->i_pid++;
// 		if (data->forking->i_fd > 0)
// 		{
// 			close(data->forking->fds[data->forking->i_fd - 1][0]);
// 		}
// 	}
// 	if (!node->command[0] && node->redirection->heredoc_count > 0
// 		&& node->redirection->redirection_count == 0)
// 		data->empty_prev_node = 1;
// 	else
// 		data->empty_prev_node = 0;
// 	return (exit_status);
// }

static void	setup_pipe_fds(t_minishell *data)
{
	if (pipe(data->forking->fds[data->forking->i_fd]) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

static void	handle_empty_command_child(t_minishell *data)
{
	close(data->forking->fds[data->forking->i_fd][0]);
	close(data->forking->fds[data->forking->i_fd][1]);
	close_heredoc_fds_p(data);
	free_all(data, 1);
	exit(0);
}

static void	setup_stdin_for_pipe(t_minishell *data, t_ast_node *node)
{
	if (data->forking->completed_piping > 0 && data->empty_prev_node == 0)
	{
		dup2(data->forking->fds[data->forking->i_fd - 1][0], STDIN_FILENO);
	}
	else if (data->forking->completed_piping > 0 && data->empty_prev_node == 1)
	{
		if (data->forking->pipe_count > 1)
		{
			dup2(node->parent->left->right->redirection->heredoc_fd[0],
				STDIN_FILENO);
			close(node->parent->left->right->redirection->heredoc_fd[0]);
		}
		else if (data->forking->pipe_count == 1)
		{
			dup2(node->parent->left->redirection->heredoc_fd[0], STDIN_FILENO);
			close(node->parent->left->redirection->heredoc_fd[0]);
		}
	}
}

static void	setup_stdout_for_pipe(t_minishell *data)
{
	if ((data->forking->completed_piping < data->forking->pipe_count))
	{
		dup2(data->forking->fds[data->forking->i_fd][1], STDOUT_FILENO);
	}
}

static void	close_all_pipe_fds(t_minishell *data)
{
	int	i;

	i = 0;
	while (i <= data->forking->i_fd)
	{
		close(data->forking->fds[i][0]);
		close(data->forking->fds[i][1]);
		i++;
	}
}

static void	execute_pipe_child(t_minishell *data, t_ast_node *node)
{
	int	exit_status;

	exit_status = 0;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!node->command[0])
	{
		handle_empty_command_child(data);
	}
	setup_stdin_for_pipe(data, node);
	setup_stdout_for_pipe(data);
	close_all_pipe_fds(data);
	if (node->redirection->types[0] != -1)
	{
		if (execute_redirection(node, data))
		{
			free_all(data, 1);
			exit(1);
		}
	}
	exit_status = execute_command(data, node);
	if (node->redirection->heredoc_count > 0)
		close_heredoc_fds_c(data);
	free_all(data, 1);
}

static void	handle_pipe_parent(t_minishell *data, t_ast_node *node, int pid)
{
	close(data->forking->fds[data->forking->i_fd][1]);
	if (!node->command[0]
		|| data->forking->completed_piping == data->forking->pipe_count)
		close(data->forking->fds[data->forking->i_fd][0]);
	data->forking->pids[data->forking->i_pid] = pid;
	data->forking->i_pid++;
	if (data->forking->i_fd > 0)
	{
		close(data->forking->fds[data->forking->i_fd - 1][0]);
	}
}

static void	update_empty_prev_node(t_minishell *data, t_ast_node *node)
{
	if (!node->command[0] && node->redirection->heredoc_count > 0
		&& node->redirection->redirection_count == 0)
		data->empty_prev_node = 1;
	else
		data->empty_prev_node = 0;
}

int	execute_pipe_command(t_minishell *data, t_ast_node *node)
{
	int	pid;
	int	exit_status;

	exit_status = 0;
	data->args_count = ft_count_tds(node->command);
	setup_pipe_fds(data);
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
		execute_pipe_child(data, node);
	}
	else
	{
		handle_pipe_parent(data, node, pid);
	}
	update_empty_prev_node(data, node);
	return (exit_status);
}

// int	tree_execution(t_ast_node *lowest_node, t_minishell *data)
// {
// 	t_ast_node	*node;
// 	t_ast_node	*temp_node;
// 	int			status;
// 	int			i;
// 	int			exit_status;
// 	int			sig;

// 	exit_status = 0;
// 	node = lowest_node;
// 	init_fds(data);
// 	init_pids(data);
// 	data->stdin_backup = -1;
// 	data->heredoc_backup = -1;
// 	node = lowest_node;
// 	sig = 0;
// 	while (node && !sig)
// 	{
// 		if ((node->type == COMMAND && node->redirection
// 				&& node->redirection->heredoc_count > 0))
// 		{
// 			sig = heredoc(data, node, 0);
// 		}
// 		if (node->type == PIPE)
// 		{
// 			temp_node = node->right;
// 			if (temp_node->type == COMMAND && temp_node->redirection
// 				&& temp_node->redirection->heredoc_count > 0)
// 			{
// 				sig = heredoc(data, temp_node, 1);
// 			}
// 		}
// 		if (node->parent)
// 			node = node->parent;
// 		else
// 			break ;
// 	}
// 	if (sig == 1)
// 	{
// 		close_heredoc_fds_p(data);
// 		return (1);
// 	}
// 	node = lowest_node;
// 	while (node)
// 	{
// 		if (node->type == COMMAND)
// 		{
// 			if (node->parent && node->parent->type == PIPE)
// 			{
// 				data->status = execute_pipe_command(data, node);
// 				data->forking->i_fd++;
// 				data->forking->completed_piping++;
// 			}
// 			else if (!node->parent)
// 			{
// 				data->status = execute_single_command(data, node);
// 			}
// 		}
// 		else if (node->type == PIPE)
// 		{
// 			temp_node = node->right;
// 			data->status = execute_pipe_command(data, temp_node);
// 			data->forking->i_fd++;
// 			data->forking->completed_piping++;
// 		}
// 		if (node->parent)
// 			node = node->parent;
// 		else
// 			break ;
// 	}
// 	i = 0;
// 	while (i < data->forking->completed_piping)
// 	{
// 		waitpid(data->forking->pids[i], &data->status, 0);
// 		i++;
// 	}
// 	if (data->forking->pipe_count > 0)
// 	{
// 		if (WIFSIGNALED(data->status))
// 		{
// 			sig = WTERMSIG(data->status);
// 			if (sig == SIGINT)
// 			{
// 				write(1, "\n", 1);
// 				data->status = 0;
// 			}
// 		}
// 		else if (WIFEXITED(data->status))
// 		{
// 			data->status = WEXITSTATUS(data->status);
// 		}
// 	}
// 	if (data->heredoc_backup != -1)
// 		close(data->heredoc_backup);
// 	if (data->stdin_backup != -1)
// 		close(data->stdin_backup);
// 	i = 0;
// 	while (i < data->forking->i_fd)
// 	{
// 		if (data->forking->fds[i])
// 		{
// 			close(data->forking->fds[i][0]);
// 			close(data->forking->fds[i][1]);
// 		}
// 		i++;
// 	}
// 	signal(SIGINT, handle_sigint);
// 	signal(SIGQUIT, handle_sigquit);
// 	close_heredoc_fds_p(data);
// 	return (data->status);
// }
static int	setup_execution_context(t_minishell *data)
{
	init_fds(data);
	init_pids(data);
	data->stdin_backup = -1;
	data->heredoc_backup = -1;
	return (0);
}

static int	handle_command_heredoc(t_minishell *data, t_ast_node *node)
{
	int	sig;

	sig = 0;
	if (node->type == COMMAND && node->redirection
		&& node->redirection->heredoc_count > 0)
	{
		sig = heredoc(data, node, 0);
	}
	return (sig);
}

static int	handle_pipe_heredoc(t_minishell *data, t_ast_node *node)
{
	int			sig;
	t_ast_node	*temp_node;

	sig = 0;
	if (node->type == PIPE)
	{
		temp_node = node->right;
		if (temp_node->type == COMMAND && temp_node->redirection
			&& temp_node->redirection->heredoc_count > 0)
		{
			sig = heredoc(data, temp_node, 1);
		}
	}
	return (sig);
}

static int	process_heredocs(t_ast_node *lowest_node, t_minishell *data)
{
	t_ast_node	*node;
	int			sig;

	node = lowest_node;
	sig = 0;
	while (node && !sig)
	{
		sig = handle_command_heredoc(data, node);
		if (sig)
			return (sig);
		sig = handle_pipe_heredoc(data, node);
		if (sig)
			return (sig);
		if (node->parent)
			node = node->parent;
		else
			break ;
	}
	return (sig);
}

static void	handle_command_execution(t_minishell *data, t_ast_node *node)
{
	if (node->parent && node->parent->type == PIPE)
	{
		data->status = execute_pipe_command(data, node);
		data->forking->i_fd++;
		data->forking->completed_piping++;
	}
	else if (!node->parent)
	{
		data->status = execute_single_command(data, node);
	}
}

static void	handle_pipe_execution(t_minishell *data, t_ast_node *node)
{
	t_ast_node	*temp_node;

	if (node->type == PIPE)
	{
		temp_node = node->right;
		data->status = execute_pipe_command(data, temp_node);
		data->forking->i_fd++;
		data->forking->completed_piping++;
	}
}

static void	execute_commands(t_ast_node *lowest_node, t_minishell *data)
{
	t_ast_node	*node;

	node = lowest_node;
	while (node)
	{
		if (node->type == COMMAND)
		{
			handle_command_execution(data, node);
		}
		else
		{
			handle_pipe_execution(data, node);
		}
		if (node->parent)
			node = node->parent;
		else
			break ;
	}
}

static void	wait_for_children(t_minishell *data)
{
	int	i;

	i = 0;
	while (i < data->forking->completed_piping)
	{
		waitpid(data->forking->pids[i], &data->status, 0);
		i++;
	}
}

static void	handle_signal_status(t_minishell *data)
{
	int	sig;

	if (data->forking->pipe_count > 0)
	{
		if (WIFSIGNALED(data->status))
		{
			sig = WTERMSIG(data->status);
			if (sig == SIGINT)
			{
				write(1, "\n", 1);
				data->status = 0;
			}
		}
		else if (WIFEXITED(data->status))
		{
			data->status = WEXITSTATUS(data->status);
		}
	}
}

static void	close_backup_fds(t_minishell *data)
{
	if (data->heredoc_backup != -1)
		close(data->heredoc_backup);
	if (data->stdin_backup != -1)
		close(data->stdin_backup);
}

static void	close_pipe_fds(t_minishell *data)
{
	int	i;

	i = 0;
	while (i < data->forking->i_fd)
	{
		if (data->forking->fds[i])
		{
			close(data->forking->fds[i][0]);
			close(data->forking->fds[i][1]);
		}
		i++;
	}
}

static void	restore_signals_and_cleanup(t_minishell *data)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	close_heredoc_fds_p(data);
}

int	tree_execution(t_ast_node *lowest_node, t_minishell *data)
{
	int	sig;

	setup_execution_context(data);
	sig = process_heredocs(lowest_node, data);
	if (sig == 1)
	{
		close_heredoc_fds_p(data);
		return (1);
	}
	execute_commands(lowest_node, data);
	wait_for_children(data);
	handle_signal_status(data);
	close_backup_fds(data);
	close_pipe_fds(data);
	restore_signals_and_cleanup(data);
	return (data->status);
}
