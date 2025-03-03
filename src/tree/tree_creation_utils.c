/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_creation_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshein <lshein@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 06:09:08 by lshein            #+#    #+#             */
/*   Updated: 2025/03/03 06:09:09 by lshein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	handle_pipe_node(t_ast_node **head, char **cmd, t_minishell *data,
		int count)
{
	t_ast_node	*temp;
	t_ast_node	*temp_head;
	char		*temp_input;

	if (!(*head))
	{
		*head = create_node(PIPE, NULL, data, 1);
		temp = create_node(COMMAND, cmd, data, count);
		add_right_node(head, temp);
		return ;
	}
	temp_head = create_node(PIPE, NULL, data, 1);
	temp = create_node(COMMAND, cmd, data, count);
	add_left_node(head, temp_head);
	*head = temp_head;
	add_right_node(head, temp);
}

void	handle_single_command(t_ast_node **head, char **cmd, t_minishell *data,
		int count)
{
	t_ast_node	*temp;

	if (!(*(head)))
	{
		*head = create_node(COMMAND, cmd, data, count);
		data->tree->lowest_node = *head;
	}
	else
	{
		temp = create_node(COMMAND, cmd, data, count);
		add_left_node(head, temp);
		data->tree->lowest_node = temp;
		temp = NULL;
	}
}

void	reset_args(char **args, int counter)
{
	int	i;

	i = 0;
	while (i < counter)
	{
		args[i] = NULL;
		i++;
	}
}

void	process_pipe_node(t_ast_node **head, t_minishell *data, int *counter,
		int i)
{
	char	*cmd[256];
	int		j;

	j = 0;
	while (j < *counter - 1)
	{
		cmd[j] = data->args[i + j + 1];
		j++;
	}
	cmd[j] = NULL;
	handle_pipe_node(head, cmd, data, *counter - 1);
	*counter = 0;
	data->forking->pipe_count += 1;
}

void	process_single_command(t_ast_node **head, t_minishell *data,
		int *counter, int i)
{
	char	*cmd[256];
	int		j;

	j = 0;
	while (j <= *counter)
	{
		cmd[j] = data->args[i + j];
		j++;
	}
	cmd[j] = NULL;
	handle_single_command(head, cmd, data, *counter);
	*counter = 0;
}
