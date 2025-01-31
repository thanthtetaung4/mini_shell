/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 15:31:26 by taung             #+#    #+#             */
/*   Updated: 2025/01/27 09:02:15 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	free_all(t_minishell *data)
{
	if (data->env)
		ft_lstclear(&data->env, env_free);
	if (data->export)
		ft_lstclear(&data->export, env_free);
	if (data->args)
		free_cmd(&data->args);
	rl_clear_history();
}
