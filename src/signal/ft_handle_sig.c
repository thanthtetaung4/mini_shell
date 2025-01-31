/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_sig.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 07:22:20 by taung             #+#    #+#             */
/*   Updated: 2025/01/31 10:46:28 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../header/minishell.h"

int	g_shell_status;

void	handle_sigint(int sig)
{
	// (void)sig;
	// write(1, "\n", 1);
	// g_shell_status = 130;
	// rl_on_new_line();
	// rl_replace_line("", 0);
	// rl_replace_line("\033[31m✘\033[0m minishell$ ", 0);
	// rl_redisplay();

	(void)sig;
    write(1, "\n", 1);  // Print a newline after Ctrl+C
    g_shell_status = 130;  // Set the status code to indicate Ctrl+C
    rl_replace_line("", 0);  // Clear the current line
    rl_on_new_line();  // Signal readline to expect a new line
	
    // Now we display the error prompt with the red ✘ and error indication
    // if (!g_shell_status)
    //     rl_replace_line("minishell$ ", 0);
    // else
    //     rl_replace_line("\033[1;31m this should be displayed", 0);
    // rl_redisplay();
}

void	handle_sigquit(int sig)
{
	(void)sig;
	write(2,"\b\b  \b\b", 6);
	g_shell_status = 0;
}
