/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_sig.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 07:22:20 by taung             #+#    #+#             */
/*   Updated: 2025/02/10 09:42:23 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int		g_shell_status;

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);  // Print a newline after Ctrl+C
	// ioctl(STDIN_FILENO, TIOCSTI, "\n");
	g_shell_status = 130;   // Set the status code to indicate Ctrl+C
	rl_on_new_line();       // Signal readline to expect a new line
	rl_replace_line("", 0); // Clear the current line
	// rl_redisplay();
}

void	handle_sigquit(int sig)
{
	(void)sig;
	write(1, "\033[2K\r", 4);
	rl_on_new_line();
	rl_redisplay();
	g_shell_status = 131;
}
