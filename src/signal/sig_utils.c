/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshein <lshein@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:45:57 by lshein            #+#    #+#             */
/*   Updated: 2025/03/04 15:05:37 by lshein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

extern int			g_sig_status;

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_sig_status = 1;
}

void	handle_sigquit(int sig)
{
	(void)sig;
	write(1, "\033[2K\r", 4);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_heredoc_sigint(int sig)
{
	(void)sig;
	g_sig_status = 1;
	rl_event_hook = NULL;
	rl_done = 1;
}

void	signal_print_newline(int signal)
{
	(void)signal;
	g_sig_status = 1;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
}
