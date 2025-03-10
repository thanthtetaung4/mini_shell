/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshein <lshein@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 05:57:29 by lshein            #+#    #+#             */
/*   Updated: 2025/03/03 06:09:33 by lshein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_ast_node	*create_tree(t_minishell *data)
{
	t_ast_node	*head;
	int			i;
	int			counter;

	i = data->args_count - 1;
	counter = 0;
	head = NULL;
	while (i >= 0)
	{
		counter++;
		if (ft_strcmp(data->args[i], "|") == 0)
		{
			process_pipe_node(&head, data, &counter, i);
		}
		else if (i == 0)
		{
			process_single_command(&head, data, &counter, i);
		}
		i--;
	}
	return (data->tree->lowest_node);
}
