/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:33:07 by taung             #+#    #+#             */
/*   Updated: 2025/03/06 00:27:54 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int			g_sig_status;

int	is_valid_cmd(char *input)
{
	if (!check_syntax_errors(input))
		return (0);
	if (!count_quotes(input))
		return (0);
	return (1);
}

void	handle_eof(t_minishell *data)
{
	write(1, "\nexit\n", 6);
	free_all(data, 0);
	exit(0);
}

int	is_runable(char *input)
{
	int	i;

	i = 0;
	while(input[i])
	{
		if (input[i] != ' ' && input[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}

void	main_loop_helper(t_minishell *data, t_ast_node *node)
{
	add_history(data->input);
	data->input = ft_remove_tabs(data->input);
	if (!is_runable(data->input))
		return ;
	data->input = ft_insert_spaces(data->input);
	data->args = split_args(data->input);
	data->args_count = ft_count_tds(data->args);
	// ft_interpret(data);
	// remove_cmd_quote(data);
	// remove_empty_args(data);
	node = create_tree(data);
	data->status = tree_execution(node, data);
	free_cmd(&data->args);
	free_tree(node);
	reset_forking_data(data);
	node = NULL;
}

void	main_loop(t_minishell *data, t_ast_node *node)
{
	while (1)
	{
		g_sig_status = 0;
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, handle_sigquit);
		data->input = readline("minishell$ ");
		if (g_sig_status)
			data->status = 130;
		if (data->input == NULL)
			handle_eof(data);
		if (data->input && *data->input)
		{
			if (!is_valid_cmd(data->input))
			{
				data->status = 1;
				free(data->input);
				continue ;
			}
			main_loop_helper(data, node);
		}
		free(data->input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	data;
	t_ast_node	*node;

	(void)argc;
	(void)argv;
	init_data(&data, envp);
	node = NULL;
	main_loop(&data, node);
	return (0);
}
