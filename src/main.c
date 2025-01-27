/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:33:07 by taung             #+#    #+#             */
/*   Updated: 2025/01/27 06:29:41 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../header/minishell.h"
// #include <readline/readline.h>
// #include <readline/history.h>

// int main()
// {
// 	char *argv[] = {NULL, "-l", NULL};
// 	printf("hello world\n");
// 	while(1)
// 	{
// 		char *line = readline("minishell$ ");
// 		printf("%s\n", line);
// 		execve(line,argv, NULL);
// 	}
// }

/*
// Testing execution
// executing OK no piping
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int	main(void)
{
	char	*input;
	pid_t	pid;
			char *args[256];
	char	*token;
	int		i;

	while (1) {
		// Prompt for input
		input = readline("Enter a command (or 'exit' to quit): ");
		if (input == NULL) {
			printf("Error reading input. Exiting.\n");
			break ;
		}
		// Add to readline history
		add_history(input);
		// Exit condition
		if (strcmp(input, "exit") == 0) {
			free(input);
			break ;
		}
		// Fork a child process
		pid = fork();
		if (pid < 0) {
			perror("fork");
			free(input);
			continue ;
		}
		if (pid == 0) {
			// Child process
			printf("Child process (PID: %d) executing: %s\n", getpid(), input);
			// Split the input into command and arguments
			token = strtok(input, " ");
			i = 0;
			while (token != NULL) {
				args[i++] = token;
				token = strtok(NULL, " ");
			}
			args[i] = NULL; // Null-terminate the argument list
			// Execute the command
			if (execve(args[0], args, NULL) == -1) {
				perror("execve");
				exit(EXIT_FAILURE);
			}
		} else {
			// Parent process
			printf("Parent process (PID: %d) waiting for child (PID: %d).\n",
				getpid(), pid);
			// Wait for the child to finish
			wait(NULL);
			printf("Child process finished.\n");
		}
		// Free the input buffer
		free(input);
	}
	printf("Exiting program.\n");
	return (0);
}
*/

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <readline/readline.h>
// #include <readline/history.h>
// #include <unistd.h>
// #include <termios.h>
// #include <signal.h>

// // Node structure for environment variables
// typedef struct s_env
// {
// 	char *key;
// 	char *value;
// 	struct s_env *next;
// } t_env;

// // Function to create a new environment node
// t_env *create_env_node(char *env_str)
// {
// 	t_env *new_node;
// 	char *equals_pos;

// 	new_node = (t_env *)malloc(sizeof(t_env));
// 	if (!new_node)
// 		return (NULL);

// 	equals_pos = strchr(env_str, '=');
// 	if (!equals_pos)
// 	{
// 		free(new_node);
// 		return (NULL);
// 	}

// 	// Calculate lengths for key and value
// 	size_t key_len = equals_pos - env_str;
// 	size_t value_len = strlen(equals_pos + 1);

// 	// Allocate and copy key
// 	new_node->key = (char *)malloc(key_len + 1);
// 	if (!new_node->key)
// 	{
// 		free(new_node);
// 		return (NULL);
// 	}
// 	strncpy(new_node->key, env_str, key_len);
// 	new_node->key[key_len] = '\0';

// 	// Allocate and copy value
// 	new_node->value = (char *)malloc(value_len + 1);
// 	if (!new_node->value)
// 	{
// 		free(new_node->key);
// 		free(new_node);
// 		return (NULL);
// 	}
// 	strcpy(new_node->value, equals_pos + 1);

// 	new_node->next = NULL;
// 	return (new_node);
// }

// // Function to add node to the end of the list
// void add_env_node(t_env **head, t_env *new_node)
// {
// 	t_env *current;

// 	if (!*head)
// 	{
// 		*head = new_node;
// 		return ;
// 	}

// 	current = *head;
// 	while (current->next)
// 		current = current->next;
// 	current->next = new_node;
// }

// // Function to load environment into linked list
// t_env *load_environment(char **envp)
// {
// 	t_env *env_list = NULL;
// 	t_env *new_node;
// 	int i;

// 	i = 0;
// 	while (envp[i])
// 	{
// 		new_node = create_env_node(envp[i]);
// 		if (new_node)
// 			add_env_node(&env_list, new_node);
// 		i++;
// 	}
// 	return (env_list);
// }

// // Function to get environment variable value
// char *get_env_value(t_env *env_list, const char *key)
// {
// 	t_env *current = env_list;

// 	while (current)
// 	{
// 		if (strcmp(current->key, key) == 0)
// 			return (current->value);
// 		current = current->next;
// 	}
// 	return (NULL);
// }

// // Function to free the entire environment list
// void free_env_list(t_env *head)
// {
// 	t_env *current;
// 	t_env *next;

// 	current = head;
// 	while (current)
// 	{
// 		next = current->next;
// 		free(current->key);
// 		free(current->value);
// 		free(current);
// 		current = next;
// 	}
// }

// 	// Example usage in main
// int main(int argc, char **argv, char **envp)
// {
// 	t_env *env_list;
// 	char *input;
// 	struct termios term;

// 	// Load environment variables into linked list
// 	env_list = load_environment(envp);

// 	printf("=================================\n");
// 	printf("%s\n",envp[0]);
// 	printf("=================================\n");
// 	// Set up terminal attributes
// 	tcgetattr(STDIN_FILENO, &term);
// 	term.c_lflag &= ~(ECHOCTL); // Disable control character echoing
// 	tcsetattr(STDIN_FILENO, TCSANOW, &term);

// 	// Set up signal handling
// 	signal(SIGINT, SIG_IGN);

// 	while (1)
// 	{
// 		// Use readline for input
// 		input = readline("minishell> ");
// 		if (!input)
// 			break ;

// 		// Add to history if not empty
// 		if (*input)
// 			add_history(input);

// 		// Example: get and print an environment variable
// 		if (strncmp(input, "get ", 4) == 0)
// 		{
// 			char *value = get_env_value(env_list, input + 4);
// 			if (value)
// 				printf("%s=%s\n", input + 4, value);
// 			else
// 				printf("Environment variable not found\n");
// 		}
// 		else if (strcmp(input, "exit") == 0)
// 		{
// 			free(input);
// 			break ;
// 		}

// 		free(input);
// 		rl_on_new_line();
// 	}

// 	// Clean up
// 	rl_clear_history();
// 	free_env_list(env_list);
// 	return (0);
// }

#include "../header/minishell.h"

int	init_data(t_minishell *data, char **envp)
{
	data->env = NULL;
	data->export = NULL;
	data->env = (load_env(envp));
	data->status = 0;
	data->forking = malloc(sizeof(t_forking));
	data->forking->pids = NULL;
	data->forking->pipe_count = 0;
	data->forking->pipe_fds = NULL;
	data->forking->redirection_count = 0;
	data->forking->redirection_fds = NULL;
	data->prev_dir = getcwd(NULL, 0);
	load_export_vars(data);
	return (1);
}

int	check_syntax_errors(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (ft_isalnum(input[i]) == 0 && input[i] != ' ' && input[i] != '/'
			&& input[i] != '.' && input[i] != '=' && input[i] != '-'
			&& input[i] != '_' && input[i] != '"' && input[i] != '\''
			&& input[i] != '$' && input[i] != '>' && input[i] != '<')
		{
			printf("minishell: syntax error near unexpected token `%c'\n",
				input[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

int	count_quotes(char *input)
{
	int	s_quote_count;
	int	d_quote_count;
	int	i;

	i = -1;
	s_quote_count = 0;
	d_quote_count = 0;
	while (input[++i])
	{
		if (input[i] == '"')
			d_quote_count++;
		if (input[i] == '\'')
			s_quote_count++;
	}
	if (s_quote_count % 2 != 0)
	{
		printf("minishell: syntax error near unexpected token `'\n");
		return (0);
	}
	if (d_quote_count % 2 != 0)
	{
		printf("minishell: syntax error near unexpected token `\"\n");
		return (0);
	}
	return (1);
}

int	is_valid_cmd(char *input)
{
	if (!check_syntax_errors(input))
		return (0);
	if (!count_quotes(input))
		return (0);
	return (1);
}
int	main(int argc, char **argv, char **envp)
{
	t_minishell	data;
	char		*input;
	t_ast_node	*node;

	init_data(&data, envp);
	node = NULL;
	//////
	// input = "ls -l < grep";
	// node = create_tree(input, &data);
	// visualize_tree(node);
	////////
	while (1)
	{
		if (!data.status)
			input = readline("minishell$ ");
		else
			input = readline("\033[31m✘\033[0m minishell$ ");
		if (input && *input && is_valid_cmd(input))
		{
			add_history(input);
			data.args = ft_split_quoted(input, ' ');
			data.args_count = ft_count_tds(data.args);
			ft_interpret(&data);
			remove_quotes(&data);
			data.status = ft_exec(&data);
			free_cmd(data.args);
			// this bloack needs to be changed
			// change to create tree and then exe from tree
		}
		free(input);
	}
	free_all(&data);
}
