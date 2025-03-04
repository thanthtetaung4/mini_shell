/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_sig.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 07:22:20 by taung             #+#    #+#             */
/*   Updated: 2025/03/04 18:08:35 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int		g_sig_status;

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
	// char	c;

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

static int	check_sig(void)
{
	if (g_sig_status)
	{
		rl_done = 1;
		return (1);
	}
	return (0);
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
	rl_event_hook = check_sig;
}
