/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_sig.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 07:22:20 by taung             #+#    #+#             */
/*   Updated: 2025/02/12 06:00:45 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int		g_shell_status;

void	handle_sigint(int sig)
{
	(void)sig;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	// printf("%d\n", getpid());
	// write(1, "\n", 1);         // Print a newline
	rl_on_new_line();       // Signal readline to expect a new line
	rl_replace_line("", 0); // Clear the current line
	// rl_redisplay();         // Update the display
	g_shell_status = 130;   // Set the status code to indicate Ctrl+C
}

void	handle_sigquit(int sig)
{
	(void)sig;
	write(1, "\033[2K\r", 4);
	rl_on_new_line();
	rl_redisplay();
	g_shell_status = 131;
}


void	handle_sigint_child(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(130);
}

void	handle_sigquit_child(int sig)
{
	(void)sig;
	write(1, "Quit: (core dumped)\n", 20);
	exit(131);
}

void setup_child_signals(void)
{
    struct sigaction sa_int, sa_quit;

    sa_int.sa_handler = handle_sigint_child;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;
    sigaction(SIGINT, &sa_int, NULL);

    sa_quit.sa_handler = handle_sigquit_child;
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = 0;
    sigaction(SIGQUIT, &sa_quit, NULL);
}
