/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshein <lshein@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:33:07 by taung             #+#    #+#             */
/*   Updated: 2025/03/08 06:49:59 by lshein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int		g_sig_status;

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

void	main_loop_helper(t_minishell *data, t_ast_node *node)
{
	data->input = ft_insert_spaces(data->input);
	data->args = split_args(data->input);
	data->args_count = ft_count_tds(data->args);
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
		set_up_main_sig();
		data->input = readline("minishell$ ");
		status_change(data);
		if (data->input && *data->input)
		{
			add_history(data->input);
			data->input = ft_remove_tabs(data->input);
			if (!is_runable(data->input))
			{
				data->status = 0;
				free(data->input);
				continue ;
			}
			if (!is_valid_cmd(data->input))
			{
				data->status = 2;
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
