/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:23:27 by taung             #+#    #+#             */
/*   Updated: 2024/12/17 03:50:50 by taung            ###   ########.fr       */
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

// executing OK no piping
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

int main()
{
	char *input;

	while (1) {
		// Prompt for input
		input = readline("Enter a command (or 'exit' to quit): ");

		if (input == NULL) {
			printf("Error reading input. Exiting.\n");
			break;
		}

		// Add to readline history
		add_history(input);

		// Exit condition
		if (strcmp(input, "exit") == 0) {
			free(input);
			break;
		}

		// Fork a child process
		pid_t pid = fork();

		if (pid < 0) {
			perror("fork");
			free(input);
			continue;
		}

		if (pid == 0) {
			// Child process
			printf("Child process (PID: %d) executing: %s\n", getpid(), input);

			// Split the input into command and arguments
			char *args[256];
			char *token = strtok(input, " ");
			int i = 0;

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
			printf("Parent process (PID: %d) waiting for child (PID: %d).\n", getpid(), pid);

			// Wait for the child to finish
			wait(NULL);
			printf("Child process finished.\n");
		}

		// Free the input buffer
		free(input);
	}

	printf("Exiting program.\n");
	return 0;
}
