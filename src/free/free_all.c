/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 15:31:26 by taung             #+#    #+#             */
/*   Updated: 2025/02/17 07:07:31 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	free_all(t_minishell *data, int free_execution_data)
{
	if (free_execution_data)
	{
		if (data->tree->lowest_node)
			free_tree(data->tree->lowest_node);
		if (data->forking)
		{
			reset_forking_data(data);

		}
	}
	if (data->tree)
		free(data->tree);
	free(data->forking);
	if (data->env)
		ft_lstclear(&data->env, env_free);
	if (data->export)
		ft_lstclear(&data->export, env_free);
	if (data->args)
		free_cmd(&data->args);
	free(data->input);
	rl_clear_history();
}
