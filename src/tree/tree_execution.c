// #include "../../header/minishell.h"
// #include <sys/wait.h>

// // void	init_forking_data(t_minishell *data)
// // {
// // 	data->forking = malloc(sizeof(t_forking));
// // 	data->forking->pids = NULL;
// // 	data->forking->pipe_count = 0;
// // 	data->forking->fds = NULL;
// // 	data->forking->redirection_count = 0;
// // 	data->forking->redirection_fds = NULL;
// // 	data->forking->heredoc_count = 0;
// // 	data->forking->i_fd = 0;
// // 	data->forking->i_pid = 0;
// // 	data->forking->i_rfd = 0;
// // 	data->forking->completed_piping = 0;
// // }

// void	init_forking_data(t_minishell *data)
// {
// 	data->forking = malloc(sizeof(t_forking));
// 	if (!data->forking)
// 		return;

// 	data->forking->pids = NULL;
// 	data->forking->pipe_count = 0;
// 	data->forking->fds = NULL;
// 	data->forking->redirection_count = 0;
// 	data->forking->redirection_fds = NULL;
// 	data->forking->heredoc_count = 0;
// 	data->forking->i_fd = 0;
// 	data->forking->i_pid = 0;
// 	data->forking->i_rfd = 0;
// 	data->forking->completed_piping = 0;
// }

// int	init_pids(t_minishell *data)
// {
// 	int	num_of_pids;

// 	num_of_pids = 0;
// 	if (data->forking->pipe_count > 0)
// 		num_of_pids = data->forking->pipe_count + 1;
// 	data->forking->pids = malloc(sizeof(int) * (num_of_pids));
// 	if (!data->forking->pids)
// 		return (-1);
// 	// printf("nums of pids => %d\n", num_of_pids);
// 	// printf("nums of pipe counts => %d\n", data->forking->pipe_count);
// 	return (num_of_pids);
// }
// // void	init_fds(t_minishell *data)
// // {
// // 	int	fds_count;
// // 	int	i;

// // 	i = 0;
// // 	if (data->forking->pipe_count > 0 || data->forking->heredoc_count > 0)
// // 	{
// // 		fds_count = data->forking->pipe_count + data->forking->heredoc_count + 1;
// // 		data->forking->fds = malloc(sizeof(int *) * fds_count);
// // 		if (!data->forking->fds)
// // 			return ;
// // 		while (i < fds_count)
// // 		{
// // 			data->forking->fds[i] = malloc(sizeof(int) * 2);
// // 			i++;
// // 		}
// // 	}
// // 	else
// // 		data->forking->fds = NULL;
// // 	if (data->forking->redirection_count > 0)
// // 		data->forking->redirection_fds = malloc(sizeof(int)
// // 				* data->forking->redirection_count);
// // 	else
// // 		data->forking->redirection_fds = NULL;
// // }

// void	init_fds(t_minishell *data)
// {
// 	int	fds_count;
// 	int	i;

// 	i = 0;
// 	if (data->forking->pipe_count > 0 || data->forking->heredoc_count > 0)
// 	{
// 		fds_count = data->forking->pipe_count + data->forking->heredoc_count + 1;
// 		data->forking->fds = malloc(sizeof(int *) * fds_count);
// 		if (!data->forking->fds)
// 			return;
// 		while (i < fds_count)
// 		{
// 			data->forking->fds[i] = malloc(sizeof(int) * 2);
// 			if (!data->forking->fds[i])
// 			{
// 				// Clean up previously allocated memory
// 				while (--i >= 0)
// 					free(data->forking->fds[i]);
// 				free(data->forking->fds);
// 				data->forking->fds = NULL;
// 				return;
// 			}
// 			i++;
// 		}
// 	}
// 	else
// 		data->forking->fds = NULL;

// 	if (data->forking->redirection_count > 0)
// 	{
// 		data->forking->redirection_fds = malloc(sizeof(int) * data->forking->redirection_count);
// 		// Initialize all redirection file descriptors to -1
// 		if (data->forking->redirection_fds)
// 		{
// 			for (i = 0; i < data->forking->redirection_count; i++)
// 				data->forking->redirection_fds[i] = -1;
// 		}
// 	}
// 	else
// 		data->forking->redirection_fds = NULL;
// }

// int	check_cmd(char *cmd)
// {
// 	char	*bultins[8];
// 	int		i;

// 	i = 0;
// 	bultins[0] = "cd";
// 	bultins[1] = "echo";
// 	bultins[2] = "env";
// 	bultins[3] = "exit";
// 	bultins[4] = "pwd";
// 	bultins[5] = "unset";
// 	bultins[6] = "export";
// 	bultins[7] = NULL;
// 	while (bultins[i] != NULL)
// 	{
// 		if (strcmp(bultins[i], cmd) == 0)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// char	*find_command_path(char *cmd, t_minishell *data)
// {
// 	char	*path_env;
// 	char	*path_dup;
// 	char	**dir;
// 	char	*full_path;
// 	int		i;

// 	if (cmd[0] == '/' || cmd[0] == '.') // Absolute or relative path
// 		return (cmd);
// 	path_env = get_env_value(data->env,"PATH");
// 	if (!path_env || ft_strlen(path_env) == 0)
// 	{
// 		ft_putstr_fd("minishell: PATH not set\n", 2);
// 		return (ft_strdup(""));
// 	}
// 	path_dup = ft_strdup(path_env);
// 	dir = ft_split(path_dup, ':');
// 	i = 0;
// 	while (dir[i])
// 	{
// 		int path_len = ft_strlen(dir[i]) + ft_strlen(cmd) + 2; // +1 for '/' and +1 for '\0'
// 		full_path = malloc(path_len);
// 		if (!full_path)
// 		{
// 			free(path_dup);
// 			return (NULL); // Memory allocation failed
// 		}
// 		ft_strlcpy(full_path, dir[i], ft_strlen(dir[i]) + 1);
// 		ft_strlcat(full_path, "/", path_len);
// 		ft_strlcat(full_path, cmd, path_len);
// 		if (access(full_path, X_OK) == 0)
// 		{ // Check if executable
// 			free(path_dup);
// 			return (full_path);
// 		}
// 		free(dir[i]);
// 		free(full_path); // Free memory if path is not valid
// 		i++;
// 	}
// 	free(path_dup);
// 	free(dir);
// 	free(path_env);
// 	return (ft_strdup(""));
// }

// int	execute_command(t_minishell *data, t_ast_node *node)
// {
// 	int		i;
// 	char	**args;
// 	char	**env_strings;
// 	struct stat path_stat;
// 	int		exit_status;

// 	if (data->args_count == 0 || ft_strlen(node->command[0]) == 0)
// 		return (0);
// 	if (check_cmd(node->command[0]) == 1)
// 	{
// 		exit_status = ft_exec(data, node);
// 		free_all(data, 1);
// 		exit(exit_status);
// 	}
// 	else if (data->forking->pipe_count == 0)
// 	{
// 		args = malloc(sizeof(char *) * (data->args_count + 1));
// 		args[0] = ft_strdup(node->command[0]);
// 		if (args[0][0] == '.' && args[0][1] == '/')
// 		{
// 			if (stat(args[0], &path_stat) == 0)
// 			{
// 				if (S_ISDIR(path_stat.st_mode))
// 				{
// 					ft_putstr_fd(" Is a directory\n", 2);
// 					free_2d_string(args);
// 					free_all(data, 1);
// 					exit (126);
// 				}
// 			}
// 			if (access(args[0], F_OK) != 0)
// 			{
// 				ft_putstr_fd(" No such file or directory\n", 2);
// 				free_2d_string(args);
// 				free_all(data, 1);
// 				exit (127);
// 			}
// 			if (access(args[0], X_OK) != 0)
// 			{
// 				ft_putstr_fd(" Permission denied\n", 2);
// 				free_2d_string(args);
// 				free_all(data, 1);
// 				exit (126);
// 			}
// 		}
// 		if (args[0][0] == '/')
// 		{
// 			if (stat(args[0], &path_stat) == 0)
// 			{
// 				if (S_ISDIR(path_stat.st_mode))
// 				{
// 					ft_putstr_fd(" Is a directory\n", 2);
// 					free_2d_string(args);
// 					free_all(data, 1);
// 					exit (126);
// 				}
// 			}
// 			if (access(args[0], F_OK) != 0)
// 			{
// 				ft_putstr_fd(" No such file or directory\n", 2);
// 				free_2d_string(args);
// 				free_all(data, 1);
// 				exit (127);
// 			}
// 		}
// 		if ((node->command[0][0] != '.' && node->command[0][1] != '/')
// 		&& ft_strncmp(node->command[0], "/bin/", 5) != 0)
// 		{
// 			args[0] = find_command_path(node->command[0], data);
// 			// printf("executed cmd: %s\n", args[0]);
// 		}

// 		i = 1;
// 		while (node->command[i] != NULL)
// 		{
// 			args[i] = ft_strdup(node->command[i]);
// 			i++;
// 		}
// 		args[i] = NULL;
// 		env_strings = get_env_strings(data->env);
// 		exit_status = execve(args[0], args, env_strings);
// 		if (exit_status == -1)
// 		{
// 				ft_putstr_fd(" command not found\n", 2);
// 				free_2d_string(args);
// 				free_cmd(&env_strings);
// 				free_all(data, 1);
// 				exit (127);
// 		}
// 		free_cmd(&env_strings);
// 		free_2d_string(args);
// 		free_all(data, 1);
// 		exit(exit_status);
// 	}
// 	else if (data->forking->pipe_count > 0)
// 	{
// 		args = malloc(sizeof(char *) * (data->args_count + 1));
// 		args[0] = node->command[0];
// 		if (args[0][0] == '.' && args[0][1] == '/')
// 		{
// 			if (stat(args[0], &path_stat) == 0)
// 			{
// 				if (S_ISDIR(path_stat.st_mode))
// 				{
// 					ft_putstr_fd(" Is a directory\n", 2);
// 					free_2d_string(args);
// 					free_all(data, 1);
// 					exit (126);
// 				}
// 			}
// 			if (access(args[0], F_OK) != 0)
// 			{
// 				ft_putstr_fd(" No such file or directory\n", 2);
// 				free_2d_string(args);
// 				free_all(data, 1);
// 				exit (127);
// 			}
// 			if (access(args[0], X_OK) != 0)
// 			{
// 				ft_putstr_fd(" Permission denied\n", 2);
// 				free_2d_string(args);
// 				free_all(data, 1);
// 				exit (126);
// 			}
// 		}
// 		if (args[0][0] == '/')
// 		{
// 			if (stat(args[0], &path_stat) == 0)
// 			{
// 				if (S_ISDIR(path_stat.st_mode))
// 				{
// 					ft_putstr_fd(" Is a directory\n", 2);
// 					free_2d_string(args);
// 					free_all(data, 1);
// 					exit (126);
// 				}
// 			}
// 			if (access(args[0], F_OK) != 0)
// 			{
// 				ft_putstr_fd(" No such file or directory\n", 2);
// 				free_2d_string(args);
// 				free_all(data, 1);
// 				exit (127);
// 			}
// 		}
// 		if ((node->command[0][0] != '.' && node->command[0][1] != '/')
// 		&& ft_strncmp(node->command[0], "/bin/", 5) != 0)
// 		{
// 			args[0] = find_command_path(node->command[0], data);
// 			// if (ft_strlen(args[0]) == 0)
// 			// {
// 			// 	ft_putstr_fd(" command not found\n", 2);
// 			// 	free_2d_string(args);
// 			// 	exit (127);
// 			// }
// 		}
// 			// args[0] = ft_strjoin("/bin/", node->command[0]);

// 		i = 1;
// 		while (node->command[i])
// 		{
// 			args[i] = ft_strdup(node->command[i]);
// 			i++;
// 		}
// 		args[i] = NULL;
// 		env_strings = get_env_strings(data->env);
// 		exit_status = execve(args[0], args, env_strings);
// 		if (exit_status == -1)
// 		{
// 				ft_putstr_fd(" command not found\n", 2);
// 				free_2d_string(args);
// 				free_cmd(&env_strings);
// 				free_all(data, 1);
// 				exit (127);
// 		}
// 		free_cmd(&env_strings);
// 		free_2d_string(args);
// 		exit(exit_status);
// 	}
// 	return (1);
// }

// // int	execute_redirection(t_ast_node *node, t_minishell *data)
// // {
// // 	int i;

// // 	i = 0;
// // 	while (node->redirection->types[i] != -1 && node->redirection->files[i] != NULL)
// // 	{
// // 		if (access(node->redirection->files[i], F_OK) == 0)
// // 		{
// // 			if (node->redirection->types[i] == OUTPUT || node->redirection->types[i] == APPEND)
// // 			{
// // 				if (access(node->redirection->files[i], W_OK) == 0 && access(node->redirection->files[i], R_OK) == 0)
// // 				{
// // 					if (node->redirection->types[i] == OUTPUT)
// // 						data->forking->redirection_fds[i] = open(node->redirection->files[i],
// // 								O_WRONLY | O_CREAT | O_TRUNC, 0644);
// // 					else if (node->redirection->types[i] == APPEND)
// // 						data->forking->redirection_fds[i] = open(node->redirection->files[i],
// // 								O_WRONLY | O_CREAT | O_APPEND, 0644);
// // 					if (data->forking->redirection_fds[i] == -1)
// // 					{
// // 						perror("open output file");
// // 						return (1);
// // 					}
// // 					dup2(data->forking->redirection_fds[i], STDOUT_FILENO);
// // 					close(data->forking->redirection_fds[i]);
// // 				}
// // 				else
// // 				{
// // 					ft_putstr_fd(node->redirection->files[i], 2);
// // 					ft_putstr_fd(": Permission denied\n", 2);
// // 					// printf("%s denied permission\n", node->file);
// // 					return (1);
// // 				}
// // 			}
// // 			else if (node->redirection->types[i] == INPUT)
// // 			{
// // 				if (access(node->redirection->files[i], R_OK) == 0)
// // 				{
// // 					data->forking->redirection_fds[i] = open(node->redirection->files[i], O_RDONLY);
// // 					if (data->forking->redirection_fds[i] == -1)
// // 					{
// // 						perror("Error opening input file");
// // 						return (1);
// // 					}
// // 					dup2(data->forking->redirection_fds[i], STDIN_FILENO);
// // 					close(data->forking->redirection_fds[i]);
// // 				}
// // 				else
// // 				{
// // 					ft_putstr_fd(node->redirection->files[i], 2);
// // 					ft_putstr_fd(": Permission denied\n", 2);
// // 					// printf("%s denied permission\n", node->file);
// // 					return (1);
// // 				}
// // 			}
// // 			else if (node->redirection->types[i] == HEREDOC)
// // 			{
// // 				heredoc(data, node);
// // 			}
// // 		}
// // 		else
// // 		{
// // 			if (node->redirection->types[i] == OUTPUT || node->redirection->types[i] == APPEND)
// // 			{

// // 					if (node->redirection->types[i] == OUTPUT)
// // 						data->forking->redirection_fds[i] = open(node->redirection->files[i],
// // 								O_WRONLY | O_CREAT | O_TRUNC, 0644);
// // 					else if (node->redirection->types[i] == APPEND)
// // 						data->forking->redirection_fds[i] = open(node->redirection->files[i],
// // 								O_WRONLY | O_CREAT | O_APPEND, 0644);
// // 					if (data->forking->redirection_fds[i] == -1)
// // 					{
// // 						// perror("open output file");
// // 						ft_putstr_fd("No such file or directory\n", 2);
// // 						return (1);
// // 					}
// // 					dup2(data->forking->redirection_fds[i], STDOUT_FILENO);
// // 					close(data->forking->redirection_fds[i]);

// // 			}
// // 			else if (node->redirection->types[i] == INPUT)
// // 			{
// // 				return (1);
// // 					// data->forking->redirection_fds[i] = open(node->redirection->files[i], O_RDONLY);
// // 					// if (data->forking->redirection_fds[i] == -1)
// // 					// {
// // 					// 	perror("Error opening input file");
// // 					// 	exit(EXIT_FAILURE);
// // 					// }
// // 					// dup2(data->forking->redirection_fds[i], STDIN_FILENO);
// // 					// close(data->forking->redirection_fds[i]);

// // 			}
// // 			else if (node->redirection->types[i] == HEREDOC)
// // 			{
// // 				heredoc(data, node);
// // 			}
// // 		}
// // 		i++;
// // 	}
// // 	return (0);
// // }

// // Completely rewritten execute_redirection function
// int execute_redirection(t_ast_node *node, t_minishell *data)
// {
//     int i = 0;
//     int fd = -1;

//     if (!node || !node->redirection || !data || !data->forking)
//         return (1);

//     // Count the number of redirections to ensure proper allocation
//     data->forking->redirection_count = 0;
//     while (node->redirection->types[data->forking->redirection_count] != -1 &&
//            node->redirection->files[data->forking->redirection_count] != NULL)
//     {
//         data->forking->redirection_count++;
//     }

//     // Allocate redirection_fds if not already allocated
//     if (data->forking->redirection_count > 0 && !data->forking->redirection_fds)
//     {
//         data->forking->redirection_fds = malloc(sizeof(int) * data->forking->redirection_count);
//         if (!data->forking->redirection_fds)
//         {
//             ft_putstr_fd("malloc error in redirection\n", 2);
//             return (1);
//         }

//         // Initialize to -1
//         for (i = 0; i < data->forking->redirection_count; i++)
//             data->forking->redirection_fds[i] = -1;
//     }

//     i = 0;
//     while (node->redirection->types[i] != -1 && node->redirection->files[i] != NULL)
//     {
//         // Handle OUTPUT redirection
//         if (node->redirection->types[i] == OUTPUT)
//         {
//             fd = open(node->redirection->files[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
//             if (fd == -1)
//             {
//                 ft_putstr_fd("minishell: ", 2);
//                 ft_putstr_fd(node->redirection->files[i], 2);
//                 ft_putstr_fd(": ", 2);
//                 perror("");
//                 return (1);
//             }

//             if (i < data->forking->redirection_count)
//                 data->forking->redirection_fds[i] = fd;

//             if (dup2(fd, STDOUT_FILENO) == -1)
//             {
//                 perror("dup2 error");
//                 close(fd);
//                 return (1);
//             }
//             close(fd);
//         }
//         // Handle APPEND redirection
//         else if (node->redirection->types[i] == APPEND)
//         {
//             fd = open(node->redirection->files[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
//             if (fd == -1)
//             {
//                 ft_putstr_fd("minishell: ", 2);
//                 ft_putstr_fd(node->redirection->files[i], 2);
//                 ft_putstr_fd(": ", 2);
//                 perror("");
//                 return (1);
//             }

//             if (i < data->forking->redirection_count)
//                 data->forking->redirection_fds[i] = fd;

//             if (dup2(fd, STDOUT_FILENO) == -1)
//             {
//                 perror("dup2 error");
//                 close(fd);
//                 return (1);
//             }
//             close(fd);
//         }
//         // Handle INPUT redirection
//         else if (node->redirection->types[i] == INPUT)
//         {
//             if (access(node->redirection->files[i], F_OK) != 0)
//             {
//                 ft_putstr_fd("minishell: ", 2);
//                 ft_putstr_fd(node->redirection->files[i], 2);
//                 ft_putstr_fd(": No such file or directory\n", 2);
//                 return (1);
//             }

//             if (access(node->redirection->files[i], R_OK) != 0)
//             {
//                 ft_putstr_fd("minishell: ", 2);
//                 ft_putstr_fd(node->redirection->files[i], 2);
//                 ft_putstr_fd(": Permission denied\n", 2);
//                 return (1);
//             }

//             fd = open(node->redirection->files[i], O_RDONLY);
//             if (fd == -1)
//             {
//                 perror("open input file");
//                 return (1);
//             }

//             if (i < data->forking->redirection_count)
//                 data->forking->redirection_fds[i] = fd;

//             if (dup2(fd, STDIN_FILENO) == -1)
//             {
//                 perror("dup2 error");
//                 close(fd);
//                 return (1);
//             }
//             close(fd);
//         }
//         // Handle HEREDOC redirection
//         else if (node->redirection->types[i] == HEREDOC)
//         {
//             if (heredoc(data, node) != 0)
//                 return (1);
//         }
//         i++;
//     }
//     return (0);
// }

// // int	execute_single_command(t_minishell *data, t_ast_node *node)
// // {
// // 	int		pid;
// // 	int		i;
// // 	int		exit_status;
// // 	int		sig;
// // 	int		stdout_fd;
// // 	int		stdin_fd;

// // 	stdout_fd = -1;
// // 	stdin_fd = -1;
// // 	exit_status = 0;
// // 	i = 0;
// // 	// printf("type: %d\n",node->redirection->types[0]);
// // 	// printf("args count: %d\n", data->args_count);
// // 	if (check_cmd(node->command[0]))
// // 	{
// // 		while (node->redirection->types[i] != -1 && node->redirection->files[i] != NULL)
// // 		{
// // 			if (node->redirection->types[i] == OUTPUT || node->redirection->types[i] == APPEND)
// // 				stdout_fd = dup(STDOUT_FILENO);
// // 			else if (node->redirection->types[i] == INPUT)
// // 				stdin_fd = dup(STDIN_FILENO);
// // 			i++;
// // 		}
// // 		if (node->redirection->types[0] != -1)
// // 		{
// // 			if (execute_redirection(node, data))
// // 				return (1);
// // 		}
// // 		exit_status = ft_exec(data, node);
// // 		if (stdout_fd != -1)
// // 		{
// // 			dup2(stdout_fd, STDOUT_FILENO);
// // 			close(stdout_fd);
// // 		}
// // 		if (stdin_fd != -1)
// // 		{
// // 			dup2(stdin_fd, STDIN_FILENO);
// // 			close(stdin_fd);
// // 		}
// // 	}
// // 	else
// // 	{
// // 		signal(SIGINT, SIG_IGN);
// // 		signal(SIGQUIT, SIG_IGN);
// // 		pid = fork();
// // 		if (pid == -1)
// // 		{
// // 			perror("fork");
// // 			return (-1);
// // 		}
// // 		else if (pid == 0)
// // 		{
// // 			signal(SIGINT, SIG_DFL);
// // 			signal(SIGQUIT, SIG_DFL);
// // 			if (node->redirection->types[0] != -1)
// // 				if (execute_redirection(node, data))
// // 					exit(0);
// // 			exit_status = execute_command(data, node);
// // 		}
// // 		else
// // 		{
// // 			wait(&exit_status);
// // 			// if (WIFSIGNALED(exit_status))
// // 			// {
// // 			// 	sig = WTERMSIG(exit_status);
// // 			// 	if (sig == SIGQUIT)
// // 			// 	{
// // 			// 		write(1, "Quit: (Core dumped)\n", 20);
// // 			// 		exit_status = 128 + sig;
// // 			// 	}
// // 			// 	else if (sig == SIGINT)
// // 			// 	{
// // 			// 		write(1, "\n", 1);
// // 			// 		exit_status = 128 + sig;
// // 			// 	}
// // 			// }
// // 			// else if (WIFEXITED(exit_status))
// // 			// {
// // 			// 	exit_status = WEXITSTATUS(exit_status);
// // 			// }
// // 		}
// // 	}
// // 	return (exit_status);
// // }

// // Improved execute_single_command function
// int execute_single_command(t_minishell *data, t_ast_node *node)
// {
//     int     pid;
//     int     i;
//     int     exit_status;
//     int     sig;
//     int     stdout_fd;
//     int     stdin_fd;

//     stdout_fd = -1;
//     stdin_fd = -1;
//     exit_status = 0;
//     i = 0;

//     // Null checks
//     if (!data || !node || !node->command || !node->redirection)
//         return (1);

//     if (node->command[0] == NULL || ft_strlen(node->command[0]) == 0)
//         return (0);

//     // Handle builtin commands
//     if (check_cmd(node->command[0]))
//     {
//         // Save original file descriptors
//         while (node->redirection->types[i] != -1 && node->redirection->files[i] != NULL)
//         {
//             if (node->redirection->types[i] == OUTPUT || node->redirection->types[i] == APPEND)
//                 stdout_fd = dup(STDOUT_FILENO);
//             else if (node->redirection->types[i] == INPUT)
//                 stdin_fd = dup(STDIN_FILENO);
//             i++;
//         }

//         // Apply redirections
//         if (node->redirection->types[0] != -1)
//         {
//             if (execute_redirection(node, data))
//             {
//                 // Restore original file descriptors
//                 if (stdout_fd != -1)
//                 {
//                     dup2(stdout_fd, STDOUT_FILENO);
//                     close(stdout_fd);
//                 }
//                 if (stdin_fd != -1)
//                 {
//                     dup2(stdin_fd, STDIN_FILENO);
//                     close(stdin_fd);
//                 }
//                 return (1);
//             }
//         }

//         // Execute builtin
//         exit_status = ft_exec(data, node);

//         // Restore original file descriptors
//         if (stdout_fd != -1)
//         {
//             dup2(stdout_fd, STDOUT_FILENO);
//             close(stdout_fd);
//         }
//         if (stdin_fd != -1)
//         {
//             dup2(stdin_fd, STDIN_FILENO);
//             close(stdin_fd);
//         }
//     }
//     else
//     {
//         signal(SIGINT, SIG_IGN);
//         signal(SIGQUIT, SIG_IGN);

//         pid = fork();
//         if (pid == -1)
//         {
//             perror("fork");
//             return (-1);
//         }
//         else if (pid == 0)
//         {
//             signal(SIGINT, SIG_DFL);
//             signal(SIGQUIT, SIG_DFL);

//             if (node->redirection->types[0] != -1)
//             {
//                 if (execute_redirection(node, data))
//                 {
//                     exit(1);
//                 }
//             }
//             exit_status = execute_command(data, node);
//             // This should not be reached
//             exit(exit_status);
//         }
//         else
//         {
//             wait(&exit_status);
//             if (WIFSIGNALED(exit_status))
//             {
//                 sig = WTERMSIG(exit_status);
//                 if (sig == SIGQUIT)
//                 {
//                     write(1, "Quit: (Core dumped)\n", 20);
//                     exit_status = 128 + sig;
//                 }
//                 else if (sig == SIGINT)
//                 {
//                     write(1, "\n", 1);
//                     exit_status = 128 + sig;
//                 }
//             }
//             else if (WIFEXITED(exit_status))
//             {
//                 exit_status = WEXITSTATUS(exit_status);
//             }
//         }
//     }
//     return (exit_status);
// }

// int	execute_pipe_command(t_minishell *data, t_ast_node *node)
// {
// 	int		pid;
// 	int		i;
// 	char	*args[256];
// 	int		**fds;
// 	int		exit_status;
// 	int		sig;

// 	i = 0;
// 	fds = data->forking->fds;
// 	exit_status = 0;
// 	// init_pids(data);
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
// 		if (data->forking->completed_piping > 0)
// 			dup2(data->forking->fds[data->forking->i_fd - 1][0], STDIN_FILENO);
// 		if (data->forking->completed_piping < data->forking->pipe_count)
// 			dup2(data->forking->fds[data->forking->i_fd][1], STDOUT_FILENO);
// 		while (i <= data->forking->i_fd)
// 		{
// 			close(data->forking->fds[i][0]);
// 			close(data->forking->fds[i][1]);
// 			i++;
// 		}
// 		if (node->redirection->types[0] != -1)
// 			if (execute_redirection(node, data))
// 				exit(1);
// 		exit_status = execute_command(data, node);
// 		free_all(data, 0);
// 	}
// 	else
// 	{
// 		data->forking->completed_piping++;
// 		close(data->forking->fds[data->forking->i_fd][1]);
// 		// close(data->forking->fds[data->forking->i_fd][0]);
// 		data->forking->pids[data->forking->i_pid] = pid;
// 		data->forking->i_pid++;
// 		if (data->forking->i_fd > 0)
// 		{
// 			close(data->forking->fds[data->forking->i_fd - 1][0]);
// 		}
// 	}
// 	return (exit_status);
// }

// // int	tree_execution(t_ast_node *lowest_node, t_minishell *data)
// // {
// // 	t_ast_node	*node;
// // 	t_ast_node	*temp_node;
// // 	int			status;
// // 	int			i;
// // 	int			exit_status;
// // 	int			sig;

// // 	exit_status = 0;
// // 	node = lowest_node;
// // 	init_fds(data);
// // 	init_pids(data);
// // 	while (node)
// // 	{
// // 		if (node->type == COMMAND)
// // 		{
// // 			if (node->parent && node->parent->type == PIPE)
// // 			{
// // 				data->status = execute_pipe_command(data, node);
// // 				data->forking->i_fd++;
// // 			}
// // 			else if (!node->parent)
// // 			{
// // 				data->status = execute_single_command(data, node);
// // 			}
// // 		}
// // 		else if (node->type == PIPE)
// // 		{
// // 			temp_node = node->right;
// // 			data->status = execute_pipe_command(data, temp_node);
// // 			data->forking->i_fd++;
// // 		}
// // 		node = node->parent;
// // 	}
// // 	i = 0;
// // 	while (i < data->forking->completed_piping)
// // 	{
// // 		// wait(&data->status);
// // 		// printf("pid %d => %d\n",i,data->forking->pids[i]);
// // 		waitpid(data->forking->pids[i], &data->status, 0);
// // 		i++;
// // 	}
// // 	if (data->forking->pipe_count == 0 && data->forking->heredoc_count == 0 && data->forking->redirection_count == 0)
// // 	{
// // 		if (WIFSIGNALED(data->status))
// // 		{
// // 			sig = WTERMSIG(data->status);
// // 			if (sig == SIGQUIT)
// // 			{
// // 				write(1, "Quit: (Core dumped)\n", 20);
// // 				data->status = 128 + sig;
// // 			}
// // 			else if (sig == SIGINT)
// // 			{
// // 				write(1, "\n", 1);
// // 				data->status = 128 + sig;
// // 			}
// // 		}
// // 		else if (WIFEXITED(data->status))
// // 		{
// // 			exit_status = WEXITSTATUS(data->status);
// // 		}
// // 	}
// // 	else
// // 	{
// // 		if (WIFSIGNALED(data->status))
// // 		{
// // 			sig = WTERMSIG(data->status);
// // 			if (sig == SIGINT)
// // 				write(1, "\n", 1);
// // 				data->status = 0;
// // 		}
// // 		else if (WIFEXITED(data->status))
// // 		{
// // 			data->status = WEXITSTATUS(data->status);
// // 		}
// // 	}
// // 	//close(data->forking->fds[data->forking->i_fd - 2][1]);
// // 	//close(data->forking->fds[data->forking->i_fd][1]);
// // 	signal(SIGINT, handle_sigint);
// // 	signal(SIGQUIT, handle_sigquit);
// // 	// printf("status: %d\n", data->status);
// // 	return (data->status);
// // }

// // Improved tree_execution function to better handle file descriptor cleanup
// int tree_execution(t_ast_node *lowest_node, t_minishell *data)
// {
//     t_ast_node  *node;
//     t_ast_node  *temp_node;
//     int         status;
//     int         i;
//     int         exit_status;
//     int         sig;

//     exit_status = 0;
//     node = lowest_node;

//     // Initialize data structures
//     init_fds(data);
//     init_pids(data);

//     // Execute command nodes
//     while (node)
//     {
//         if (node->type == COMMAND)
//         {
//             if (node->parent && node->parent->type == PIPE)
//             {
//                 data->status = execute_pipe_command(data, node);
//                 data->forking->i_fd++;
//             }
//             else if (!node->parent)
//             {
//                 data->status = execute_single_command(data, node);
//             }
//         }
//         else if (node->type == PIPE)
//         {
//             temp_node = node->right;
//             data->status = execute_pipe_command(data, temp_node);
//             data->forking->i_fd++;
//         }
//         node = node->parent;
//     }

//     // Wait for child processes
//     i = 0;
//     while (i < data->forking->completed_piping)
//     {
//         waitpid(data->forking->pids[i], &data->status, 0);
//         i++;
//     }

//     // Clean up file descriptors
//     if (data->forking->fds)
//     {
//         for (i = 0; i < data->forking->pipe_count + data->forking->heredoc_count + 1; i++)
//         {
//             if (data->forking->fds[i])
//             {
//                 if (data->forking->fds[i][0] >= 0)
//                     close(data->forking->fds[i][0]);
//                 if (data->forking->fds[i][1] >= 0)
//                     close(data->forking->fds[i][1]);
//             }
//         }
//     }

//     // Handle signals and exit status
//     if (data->forking->pipe_count == 0 && data->forking->heredoc_count == 0 && data->forking->redirection_count == 0)
//     {
//         if (WIFSIGNALED(data->status))
//         {
//             sig = WTERMSIG(data->status);
//             if (sig == SIGQUIT)
//             {
//                 write(1, "Quit: (Core dumped)\n", 20);
//                 data->status = 128 + sig;
//             }
//             else if (sig == SIGINT)
//             {
//                 write(1, "\n", 1);
//                 data->status = 128 + sig;
//             }
//         }
//         else if (WIFEXITED(data->status))
//         {
//             exit_status = WEXITSTATUS(data->status);
//         }
//     }
//     else
//     {
//         if (WIFSIGNALED(data->status))
//         {
//             sig = WTERMSIG(data->status);
//             if (sig == SIGINT)
//                 write(1, "\n", 1);
//                 data->status = 0;
//         }
//         else if (WIFEXITED(data->status))
//         {
//             data->status = WEXITSTATUS(data->status);
//         }
//     }

//     signal(SIGINT, handle_sigint);
//     signal(SIGQUIT, handle_sigquit);
//     return (data->status);
// }

#include "../../header/minishell.h"
#include <sys/wait.h>

/**
 * Initialize the forking data structure
 * This structure holds information about processes, pipes, and file descriptors
 */
void init_forking_data(t_minishell *data)
{
    if (!data)
        return;

    data->forking = malloc(sizeof(t_forking));
    if (!data->forking)
        return;

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

/**
 * Initialize the array of process IDs for tracking child processes
 * Returns the number of pids that will be tracked
 */
int init_pids(t_minishell *data)
{
    int num_of_pids;

    if (!data || !data->forking)
        return (-1);

    num_of_pids = 0;
    if (data->forking->pipe_count > 0)
        num_of_pids = data->forking->pipe_count + 1;

    data->forking->pids = malloc(sizeof(int) * (num_of_pids));
    if (!data->forking->pids)
        return (-1);

    return (num_of_pids);
}

/**
 * Initialize file descriptors for pipes and redirections
 * Allocates memory for pipe fds and redirection fds
 */
void init_fds(t_minishell *data)
{
    int fds_count;
    int i;

    if (!data || !data->forking)
        return;

    i = 0;
    data->forking->fds = NULL;
    data->forking->redirection_fds = NULL;

    // Initialize pipe file descriptors
    if (data->forking->pipe_count > 0 || data->forking->heredoc_count > 0)
    {
        fds_count = data->forking->pipe_count + data->forking->heredoc_count + 1;
        data->forking->fds = malloc(sizeof(int *) * fds_count);
        if (!data->forking->fds)
            return;

        while (i < fds_count)
        {
            data->forking->fds[i] = malloc(sizeof(int) * 2);
            if (!data->forking->fds[i])
            {
                // Clean up previously allocated memory
                while (--i >= 0)
                    free(data->forking->fds[i]);
                free(data->forking->fds);
                data->forking->fds = NULL;
                return;
            }
            // Initialize pipe file descriptors to -1
            data->forking->fds[i][0] = -1;
            data->forking->fds[i][1] = -1;
            i++;
        }
    }

    // Initialize redirection file descriptors
    if (data->forking->redirection_count > 0)
    {
        data->forking->redirection_fds = malloc(sizeof(int) * data->forking->redirection_count);
        if (!data->forking->redirection_fds)
            return;

        // Initialize all redirection file descriptors to -1
        for (i = 0; i < data->forking->redirection_count; i++)
            data->forking->redirection_fds[i] = -1;
    }
}

/**
 * Check if the command is a shell builtin
 * Returns 1 if builtin, 0 otherwise
 */
int check_cmd(char *cmd)
{
    char *builtins[8];
    int i;

    if (!cmd)
        return (0);

    i = 0;
    builtins[0] = "cd";
    builtins[1] = "echo";
    builtins[2] = "env";
    builtins[3] = "exit";
    builtins[4] = "pwd";
    builtins[5] = "unset";
    builtins[6] = "export";
    builtins[7] = NULL;

    while (builtins[i] != NULL)
    {
        if (strcmp(builtins[i], cmd) == 0)
            return (1);
        i++;
    }
    return (0);
}

/**
 * Find the full path to a command
 * Searches in the PATH environment variable
 */
char *find_command_path(char *cmd, t_minishell *data)
{
    char *path_env;
    char *path_dup;
    char **dir;
    char *full_path;
    int i;

    if (!cmd || !data)
        return (NULL);

    // Return the command as is if it's an absolute or relative path
    if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
        return (ft_strdup(cmd));

    // Get the PATH environment variable
    path_env = get_env_value(data->env, "PATH");
    if (!path_env || ft_strlen(path_env) == 0)
    {
        ft_putstr_fd("minishell: PATH not set\n", 2);
        return (ft_strdup(""));
    }

    // Split PATH into directories
    path_dup = ft_strdup(path_env);
    if (!path_dup)
    {
        free(path_env);
        return (NULL);
    }

    dir = ft_split(path_dup, ':');
    if (!dir)
    {
        free(path_dup);
        free(path_env);
        return (NULL);
    }

    // Search for the command in each directory
    i = 0;
    while (dir[i])
    {
        int path_len = ft_strlen(dir[i]) + ft_strlen(cmd) + 2; // +1 for '/' and +1 for '\0'
        full_path = malloc(path_len);
        if (!full_path)
        {
            // Clean up and return NULL on memory allocation failure
            while (dir[i])
                free(dir[i++]);
            free(dir);
            free(path_dup);
            free(path_env);
            return (NULL);
        }

        ft_strlcpy(full_path, dir[i], ft_strlen(dir[i]) + 1);
        ft_strlcat(full_path, "/", path_len);
        ft_strlcat(full_path, cmd, path_len);

        if (access(full_path, X_OK) == 0)
        {
            // Command found, clean up and return the full path
            while (dir[i])
                free(dir[i++]);
            free(dir);
            free(path_dup);
            free(path_env);
            return (full_path);
        }

        free(full_path);
        free(dir[i]);
        i++;
    }

    // Command not found
    free(dir);
    free(path_dup);
    free(path_env);
    return (ft_strdup(""));
}

/**
 * Execute a command with execve
 * Handles builtin commands and external commands
 */
int execute_command(t_minishell *data, t_ast_node *node)
{
    char **args;
    char **env_strings;
    struct stat path_stat;
    int exit_status = 0;
    int i = 0;

    if (!data || !node || !node->command)
        return (1);

    // Check if the command is empty or has no arguments
    if (data->args_count == 0 || !node->command[0] || ft_strlen(node->command[0]) == 0)
        return (0);

    // Handle builtin commands
    if (check_cmd(node->command[0]) == 1)
    {
        exit_status = ft_exec(data, node);
        free_all(data, 1);
        exit(exit_status);
    }

    // Handle external commands
    args = malloc(sizeof(char *) * (data->args_count + 1));
    if (!args)
    {
        free_all(data, 1);
        exit(1);
    }

    // Handle relative or absolute paths
    if ((node->command[0][0] == '.' && node->command[0][1] == '/') ||
        node->command[0][0] == '/')
    {
        args[0] = ft_strdup(node->command[0]);
        if (!args[0])
        {
            free(args);
            free_all(data, 1);
            exit(1);
        }

        // Check if the path is a directory
        if (stat(args[0], &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
        {
            ft_putstr_fd("minishell: ", 2);
            ft_putstr_fd(args[0], 2);
            ft_putstr_fd(": Is a directory\n", 2);
            free(args[0]);
            free(args);
            free_all(data, 1);
            exit(126);
        }

        // Check if the file exists
        if (access(args[0], F_OK) != 0)
        {
            ft_putstr_fd("minishell: ", 2);
            ft_putstr_fd(args[0], 2);
            ft_putstr_fd(": No such file or directory\n", 2);
            free(args[0]);
            free(args);
            free_all(data, 1);
            exit(127);
        }

        // Check if the file is executable
        if (access(args[0], X_OK) != 0)
        {
            ft_putstr_fd("minishell: ", 2);
            ft_putstr_fd(args[0], 2);
            ft_putstr_fd(": Permission denied\n", 2);
            free(args[0]);
            free(args);
            free_all(data, 1);
            exit(126);
        }
    }
    else
    {
        // Command without path, search in PATH
        args[0] = find_command_path(node->command[0], data);
        if (!args[0] || ft_strlen(args[0]) == 0)
        {
            ft_putstr_fd("minishell: ", 2);
            ft_putstr_fd(node->command[0], 2);
            ft_putstr_fd(": command not found\n", 2);
            free(args[0]);
            free(args);
            free_all(data, 1);
            exit(127);
        }
    }

    // Copy command arguments
    i = 1;
    while (node->command[i] != NULL)
    {
        args[i] = ft_strdup(node->command[i]);
        if (!args[i])
        {
            free_2d_string(args);
            free_all(data, 1);
            exit(1);
        }
        i++;
    }
    args[i] = NULL;

    // Get environment variables as strings
    env_strings = get_env_strings(data->env);
    if (!env_strings)
    {
        free_2d_string(args);
        free_all(data, 1);
        exit(1);
    }

    // Execute the command
    exit_status = execve(args[0], args, env_strings);

    // If execve returns, it means there was an error
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(node->command[0], 2);
    ft_putstr_fd(": command not found\n", 2);

    free_2d_string(args);
    free_cmd(&env_strings);
    free_all(data, 1);
    exit(127);
}

/**
 * Handle file redirections
 * Supports input, output, append, and heredoc redirections
 */
int execute_redirection(t_ast_node *node, t_minishell *data)
{
    int i = 0;
    int fd = -1;

    if (!node || !node->redirection || !data || !data->forking)
        return (1);

    // Count the number of redirections to ensure proper allocation
    data->forking->redirection_count = 0;
    while (node->redirection->types[data->forking->redirection_count] != -1 &&
           node->redirection->files[data->forking->redirection_count] != NULL)
    {
        data->forking->redirection_count++;
    }

    // Allocate redirection_fds if not already allocated
    if (data->forking->redirection_count > 0 && !data->forking->redirection_fds)
    {
        data->forking->redirection_fds = malloc(sizeof(int) * data->forking->redirection_count);
        if (!data->forking->redirection_fds)
        {
            ft_putstr_fd("minishell: malloc error in redirection\n", 2);
            return (1);
        }

        // Initialize to -1
        for (i = 0; i < data->forking->redirection_count; i++)
            data->forking->redirection_fds[i] = -1;
    }

    i = 0;
    while (node->redirection->types[i] != -1 && node->redirection->files[i] != NULL)
    {
        // Handle OUTPUT redirection
        if (node->redirection->types[i] == OUTPUT)
        {
            fd = open(node->redirection->files[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1)
            {
                ft_putstr_fd("minishell: ", 2);
                ft_putstr_fd(node->redirection->files[i], 2);
                ft_putstr_fd(": ", 2);
                perror("");
                return (1);
            }

            if (i < data->forking->redirection_count)
                data->forking->redirection_fds[i] = fd;

            if (dup2(fd, STDOUT_FILENO) == -1)
            {
                ft_putstr_fd("minishell: dup2 error\n", 2);
                close(fd);
                return (1);
            }
            close(fd);
        }
        // Handle APPEND redirection
        else if (node->redirection->types[i] == APPEND)
        {
            fd = open(node->redirection->files[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1)
            {
                ft_putstr_fd("minishell: ", 2);
                ft_putstr_fd(node->redirection->files[i], 2);
                ft_putstr_fd(": ", 2);
                perror("");
                return (1);
            }

            if (i < data->forking->redirection_count)
                data->forking->redirection_fds[i] = fd;

            if (dup2(fd, STDOUT_FILENO) == -1)
            {
                ft_putstr_fd("minishell: dup2 error\n", 2);
                close(fd);
                return (1);
            }
            close(fd);
        }
        // Handle INPUT redirection
        else if (node->redirection->types[i] == INPUT)
        {
            if (access(node->redirection->files[i], F_OK) != 0)
            {
                ft_putstr_fd("minishell: ", 2);
                ft_putstr_fd(node->redirection->files[i], 2);
                ft_putstr_fd(": No such file or directory\n", 2);
                return (1);
            }

            if (access(node->redirection->files[i], R_OK) != 0)
            {
                ft_putstr_fd("minishell: ", 2);
                ft_putstr_fd(node->redirection->files[i], 2);
                ft_putstr_fd(": Permission denied\n", 2);
                return (1);
            }

            fd = open(node->redirection->files[i], O_RDONLY);
            if (fd == -1)
            {
                ft_putstr_fd("minishell: ", 2);
                ft_putstr_fd(node->redirection->files[i], 2);
                ft_putstr_fd(": ", 2);
                perror("");
                return (1);
            }

            if (i < data->forking->redirection_count)
                data->forking->redirection_fds[i] = fd;

            if (dup2(fd, STDIN_FILENO) == -1)
            {
                ft_putstr_fd("minishell: dup2 error\n", 2);
                close(fd);
                return (1);
            }
            close(fd);
        }
        // Handle HEREDOC redirection
        else if (node->redirection->types[i] == HEREDOC)
        {
            if (heredoc(data, node) != 0)
                return (1);
        }
        i++;
    }
    return (0);
}

/**
 * Execute a single command (no pipes)
 * Handles builtins and external commands
 */
int execute_single_command(t_minishell *data, t_ast_node *node)
{
    int     pid;
    int     exit_status = 0;
    int     sig;
    int     stdout_fd = -1;
    int     stdin_fd = -1;
    int     i = 0;

    // Null checks
    if (!data || !node || !node->command || !node->redirection)
        return (1);

    if (node->command[0] == NULL || ft_strlen(node->command[0]) == 0)
        return (0);

    // Handle builtin commands
    if (check_cmd(node->command[0]))
    {
        // Save original file descriptors
        while (node->redirection->types[i] != -1 && node->redirection->files[i] != NULL)
        {
            if (node->redirection->types[i] == OUTPUT || node->redirection->types[i] == APPEND)
            {
                stdout_fd = dup(STDOUT_FILENO);
                if (stdout_fd == -1)
                {
                    ft_putstr_fd("minishell: dup error\n", 2);
                    return (1);
                }
            }
            else if (node->redirection->types[i] == INPUT)
            {
                stdin_fd = dup(STDIN_FILENO);
                if (stdin_fd == -1)
                {
                    if (stdout_fd != -1)
                        close(stdout_fd);
                    ft_putstr_fd("minishell: dup error\n", 2);
                    return (1);
                }
            }
            i++;
        }

        // Apply redirections
        if (node->redirection->types[0] != -1)
        {
            if (execute_redirection(node, data))
            {
                // Restore original file descriptors
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
                return (1);
            }
        }

        // Execute builtin
        exit_status = ft_exec(data, node);

        // Restore original file descriptors
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
        // Handle external commands by forking
        signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);

        pid = fork();
        if (pid == -1)
        {
            ft_putstr_fd("minishell: fork error\n", 2);
            return (1);
        }
        else if (pid == 0)
        {
            // Child process
            signal(SIGINT, SIG_DFL);
            signal(SIGQUIT, SIG_DFL);

            if (node->redirection->types[0] != -1)
            {
                if (execute_redirection(node, data))
                {
                    exit(1);
                }
            }
            execute_command(data, node);
            // This should not be reached
            exit(1);
        }
        else
        {
            // Parent process
            waitpid(pid, &exit_status, 0);
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

/**
 * Execute a command that is part of a pipe
 * Sets up the input/output redirections for the pipeline
 */
int execute_pipe_command(t_minishell *data, t_ast_node *node)
{
    int pid;
    int i;
    int exit_status = 0;

    if (!data || !node || !data->forking || !data->forking->fds)
        return (1);

    i = 0;
    data->args_count = ft_count_tds(node->command);

    // Create pipe
    if (pipe(data->forking->fds[data->forking->i_fd]) == -1)
    {
        ft_putstr_fd("minishell: pipe error\n", 2);
        return (1);
    }

    // Ignore signals in parent process
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);

    pid = fork();
    if (pid == -1)
    {
        ft_putstr_fd("minishell: fork error\n", 2);
        return (1);
    }
    else if (pid == 0)
    {
        // Child process
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);

        // Set up pipe redirections
        if (data->forking->completed_piping > 0)
        {
            if (dup2(data->forking->fds[data->forking->i_fd - 1][0], STDIN_FILENO) == -1)
            {
                ft_putstr_fd("minishell: dup2 error\n", 2);
                exit(1);
            }
        }

        if (data->forking->completed_piping < data->forking->pipe_count)
        {
            if (dup2(data->forking->fds[data->forking->i_fd][1], STDOUT_FILENO) == -1)
            {
                ft_putstr_fd("minishell: dup2 error\n", 2);
                exit(1);
            }
        }

        // Close all pipe file descriptors
        while (i <= data->forking->i_fd)
        {
            close(data->forking->fds[i][0]);
            close(data->forking->fds[i][1]);
            i++;
        }

        // Handle redirections
        if (node->redirection->types[0] != -1)
        {
            if (execute_redirection(node, data))
                exit(1);
        }

        // Execute the command
        execute_command(data, node);

        // This should not be reached
        free_all(data, 1);
        exit(1);
    }
    else
    {
        // Parent process
        data->forking->completed_piping++;

        // Close write end of pipe
        close(data->forking->fds[data->forking->i_fd][1]);

        // Store child process ID
        if (data->forking->pids)
            data->forking->pids[data->forking->i_pid++] = pid;

        // Close read end of previous pipe
        if (data->forking->i_fd > 0)
            close(data->forking->fds[data->forking->i_fd - 1][0]);
    }

    return (exit_status);
}

/**
 * Execute the command tree
 * Traverses the AST and executes commands
 */
int tree_execution(t_ast_node *lowest_node, t_minishell *data)
{
    t_ast_node  *node;
    t_ast_node  *temp_node;
    int         i;
    int         exit_status = 0;
    int         sig;

    if (!data || !lowest_node)
        return (1);

    node = lowest_node;

    // Initialize data structures
    init_fds(data);

    // Initialize PIDs array
    if (data->forking->pipe_count > 0)
    {
        if (init_pids(data) == -1)
        {
            ft_putstr_fd("minishell: memory allocation error\n", 2);
            return (1);
        }
    }

    // Execute command nodes
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

    // Wait for child processes to finish
    for (i = 0; i < data->forking->completed_piping; i++)
    {
        if (data->forking->pids && i < data->forking->pipe_count + 1)
            waitpid(data->forking->pids[i], &data->status, 0);
    }

    // Clean up file descriptors
    if (data->forking->fds)
    {
        for (i = 0; i < data->forking->pipe_count + data->forking->heredoc_count + 1; i++)
        {
            if (data->forking->fds[i])
            {
                if (data->forking->fds[i][0] >= 0)
                    close(data->forking->fds[i][0]);
                if (data->forking->fds[i][1] >= 0)
                    close(data->forking->fds[i][1]);
            }
        }
    }

    // Handle signals and exit status
    if (data->forking->pipe_count == 0 && data->forking->heredoc_count == 0 && data->forking->redirection_count == 0)
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
            data->status = WEXITSTATUS(data->status);
        }
    }
    else
    {
        if (WIFSIGNALED(data->status))
        {
            sig = WTERMSIG(data->status);
            if (sig == SIGINT)
            {
                write(1, "\n", 1);
                data->status = 130;
            }
            else if (sig == SIGQUIT)
            {
                write(1, "Quit: (Core dumped)\n", 20);
                data->status = 131;
            }
        }
        else if (WIFEXITED(data->status))
        {
            data->status = WEXITSTATUS(data->status);
        }
    }

    // Restore signal handlers
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, handle_sigquit);

    return (data->status);
}
