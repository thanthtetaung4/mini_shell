/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:33:07 by taung             #+#    #+#             */
/*   Updated: 2025/02/17 07:07:06 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

extern int	g_shell_status;

int	init_data(t_minishell *data, char **envp)
{
	data->env = NULL;
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
	while (input[i])
	{
		if (ft_isalnum(input[i]) == 0 && input[i] != ' ' && input[i] != '/'
			&& input[i] != '.' && input[i] != '=' && input[i] != '-'
			&& input[i] != '_' && input[i] != '"' && input[i] != '\''
			&& input[i] != '$' && input[i] != '>' && input[i] != '<'
			&& input[i] != '|' && input[i] != '?')
		{
			printf("minishell: syntax error near unexpected token `%c'\n",
				input[i]);
 			return (0);
		}
		i++;
	}
	return (1);
}

int	count_quotes(char *input)
{
	int	s_quote_count;
	int	d_quote_count;
	int	i;

	i = -1;
	s_quote_count = 0;
	d_quote_count = 0;
	while (input[++i])
	{
		if (input[i] == '"')
			d_quote_count++;
		if (input[i] == '\'')
			s_quote_count++;
	}
	if (s_quote_count % 2 != 0)
	{
		printf("minishell: syntax error near unexpected token `'\n");
		return (0);
	}
	if (d_quote_count % 2 != 0)
	{
		printf("minishell: syntax error near unexpected token `\"\n");
		return (0);
	}
	return (1);
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

int	main(int argc, char **argv, char **envp)
{
	t_minishell	data;
	char		*input;
	t_ast_node	*node;

	g_shell_status = 0;
	init_data(&data, envp);
	node = NULL;
	while (1)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, handle_sigquit);
		if (!g_shell_status)
			input = readline("minishell$ ");
		else
			input = readline("\033[31m✘\033[0m minishell$ ");
		if (input == NULL)
			handle_eof(&data);
		if (input && *input && is_valid_cmd(input))
		{
			add_history(input);
			data.args = ft_split_quoted(input, ' ');
			data.args_count = ft_count_tds(data.args);
			ft_interpret(&data);
			remove_quotes(&data);
			node = create_tree(&data);
			// visualize_tree(node);
			g_shell_status = tree_execution(node, &data);
			// if (data.status == 0)
			// 	printf("\033[32m✔\033[0m ");
			// data.status = ft_exec(&data);
			free_cmd(&data.args);
			free_tree(node);
			reset_forking_data(&data);
			node = NULL;
			// this bloack needs to be changed
			// change to create tree and then exe from tree
		}
		free(input);
	}
}
