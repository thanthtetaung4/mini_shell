/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_sig.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 07:22:20 by taung             #+#    #+#             */
/*   Updated: 2025/02/27 23:38:12 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int		g_sig_status;

void	handle_sigint(int sig)
{
	(void)sig;
	// ioctl(STDOUT_FILENO, TIOCSTI, "\n");
	// printf("%d\n", getpid());
	write(1, "\n", 1);         // Print a newline
	rl_on_new_line();       // Signal readline to expect a new line
	rl_replace_line("", 0); // Clear the current line
	rl_redisplay();         // Update the display
	g_sig_status = 1;   // Set the status code to indicate Ctrl+C
}

void	handle_sigquit(int sig)
{
	(void)sig;
	write(1, "\033[2K\r", 4);
	rl_on_new_line();
	rl_redisplay();
	// g_sig_status = 131;
}

void	handle_heredoc_sigint(int sig)
{
	// (void)sig;
	// // write(1, "\n", 1);
	// // ioctl(STDOUT_FILENO, TIOCSTI, "\n");
	// if (isatty(STDIN_FILENO))
	// {
	// 	ioctl(STDIN_FILENO, TIOCSTI, "\n");
    // }
	// // rl_replace_line("\n", 0);
	// rl_on_new_line();
	// // rl_redisplay();
	// g_sig_status = 1;

	(void)sig;
    g_sig_status = 1;
    ft_putstr_fd("\n", STDOUT_FILENO);
    rl_on_new_line();
    rl_replace_line("", 0);
}

void	signal_print_newline(int signal)
{
	(void)signal;
	g_sig_status = 1;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
}

void	set_signals_heredoc(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &handle_heredoc_sigint;
	sigaction(SIGINT, &act, NULL);
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}
