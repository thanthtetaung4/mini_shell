/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:33:07 by taung             #+#    #+#             */
/*   Updated: 2025/03/03 14:56:32 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

extern int	g_sig_status;

int	check_syntax_errors(char *input)
{
	int	len;

	len = ft_strlen(input);
	if ((input[len - 1] == '>' || input[len - 1] == '<'
			|| input[len - 1] == '>') && (input[len - 2] == '>'
			|| input[len - 1] == '>') && input[len - 2] == '>')
	{
		ft_putstr_fd("invalid syntax\n", 2);
		return (0);
	}
	return (1);
}

void	init_count_quotes(int *s_quote_count, int *d_quote_count,
	int *in_d_quotes, int *in_s_quotes)
{
	*s_quote_count = 0;
	*d_quote_count = 0;
	*in_d_quotes = 0;
	*in_s_quotes = 0;
}

int	print_err(int *s_quote_count, int *d_quote_count)
{
	if ((*s_quote_count) % 2 != 0)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `' || \"\n",
			2);
		return (0);
	}
	if ((*d_quote_count) % 2 != 0)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `\"\n", 2);
		return (0);
	}
	return (1);
}

int	count_quotes(char *input)
{
	int	s_quote_count;
	int	d_quote_count;
	int	i;
	int	in_d_quotes;
	int	in_s_quotes;

	i = -1;
	init_count_quotes(&s_quote_count, &d_quote_count,
		&in_d_quotes, &in_s_quotes);
	while (input[++i])
	{
		if (input[i] == '"' && !in_s_quotes)
		{
			d_quote_count++;
			in_d_quotes = !in_d_quotes;
		}
		if (input[i] == '\'' && !in_d_quotes)
		{
			s_quote_count++;
			in_s_quotes = !in_s_quotes;
		}
	}
	return (print_err(&s_quote_count, &d_quote_count));
}

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

// int	main(int argc, char **argv, char **envp)
// {
// 	t_minishell	data;
// 	t_ast_node	*node;

// 	(void)argc;
// 	(void)argv;
// 	init_data(&data, envp);
// 	node = NULL;
// 	while (1)
// 	{
// 		signal(SIGINT, handle_sigint);
// 		signal(SIGQUIT, handle_sigquit);
// 		data.input = readline("minishell$ ");
// 		if (g_sig_status)
// 			data.status = 130;
// 		if (data.input == NULL)
// 			handle_eof(&data);
// 		if (data.input && *data.input)
// 		{
// 			if (!is_valid_cmd(data.input))
// 			{
// 				data.status = 1;
// 				free(data.input);
// 				continue ;
// 			}
// 			add_history(data.input);
// 			data.input = ft_insert_spaces(data.input);
// 			data.args = split_args(data.input);
// 			data.args_count = ft_count_tds(data.args);
// 			ft_interpret(&data);
// 			remove_cmd_quote(&data);
// 			remove_empty_args(&data);
// 			node = create_tree(&data);
// 			data.status = tree_execution(node, &data);
// 			free_cmd(&data.args);
// 			free_tree(node);
// 			reset_forking_data(&data);
// 			node = NULL;
// 		}
// 		free(data.input);
// 	}
// }

void	main_loop_helper(t_minishell *data, t_ast_node *node)
{
	add_history(data->input);
	data->input = ft_insert_spaces(data->input);
	data->args = split_args(data->input);
	data->args_count = ft_count_tds(data->args);
	ft_interpret(data);
	remove_cmd_quote(data);
	remove_empty_args(data);
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
