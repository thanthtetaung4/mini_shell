/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:33:07 by taung             #+#    #+#             */
/*   Updated: 2025/02/26 04:09:39 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

extern int	g_shell_status;

int	init_data(t_minishell *data, char **envp)
{
	data->env = NULL;
	data->input = NULL;
	data->export = NULL;
	data->env = (load_env(envp));
	data->args = NULL;
	data->status = 0;
	data->tree = malloc(sizeof(t_tree));
	data->tree->lowest_node = NULL;
	init_forking_data(data);
	load_export_vars(data);
	return (1);
}

int	check_syntax_errors(char *input)
{
	int	i;

	i = 0;
	// while (input[i])
	// {
	// 	// if (ft_isalnum(input[i]) == 0 && input[i] != ' ' && input[i] != '/'
	// 	// 	&& input[i] != '.' && input[i] != '=' && input[i] != '-'
	// 	// 	&& input[i] != '_' && input[i] != '"' && input[i] != '\''
	// 	// 	&& input[i] != '$' && input[i] != '>' && input[i] != '<'
	// 	// 	&& input[i] != '|' && input[i] != '?' && input[i] != '!'
	// 	// 	&& input[i] != '\n')
	// 	if (input[i] == '&')
	// 	{
	// 		printf("minishell: syntax error near unexpected token `%c'\n",
	// 			input[i]);
 	// 		return (0);
	// 	}
	// 	i++;
	// }
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
    s_quote_count = 0;
    d_quote_count = 0;
    in_d_quotes = 0;
    in_s_quotes = 0;
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
    if (s_quote_count % 2 != 0)
    {
        ft_putstr_fd("minishell: syntax error near unexpected token `'\n", 2);
        return (0);
    }
    if (d_quote_count % 2 != 0)
    {
        ft_putstr_fd("minishell: syntax error near unexpected token `\"\n", 2);
        return (0);
    }
    return (1);
}

int	is_valid_cmd(char *input)
{
	// if (!check_syntax_errors(input))
	// 	return (0);
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

int	main(int argc, char **argv, char **envp)
{
	t_minishell	data;
	t_ast_node	*node;

	g_shell_status = 0;
	init_data(&data, envp);
	node = NULL;
	while (1)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, handle_sigquit);
		if (!g_shell_status)
			data.input = readline("minishell$ ");
		else
			data.input = readline("\033[31m✘\033[0m minishell$ ");
		if (data.input == NULL)
			handle_eof(&data);
		if (data.input && *data.input)
		{
			if (!is_valid_cmd(data.input))
			{
				g_shell_status = 1;
				continue;
			}
			add_history(data.input);
			// printf("input: %s\n", data.input);
			data.input = ft_insert_spaces(data.input);
			// printf("splitting\n");
			data.args = split_args(data.input);
			// printf("splitting done\n");
			data.args_count = ft_count_tds(data.args);
			//we can't do this here because this will make "ls | pwd" => args count 3 and when we execute pipe this is the problem
			// printf("counted\n");
			ft_interpret(&data);
			printf("----------\n");
			ft_print_args(data.args);
			printf("----------\n");
			remove_cmd_quote(&data);
			remove_empty_args(&data);
			// printf("args_count: %d\n", data.args_count);
			node = create_tree(&data);
			// visualize_tree(node);
			g_shell_status = tree_execution(node, &data);
			free_cmd(&data.args);
			free_tree(node);
			reset_forking_data(&data);
			node = NULL;
		}
		free(data.input);
	}
}
