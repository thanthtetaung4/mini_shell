/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 15:31:26 by taung             #+#    #+#             */
/*   Updated: 2025/01/18 08:02:08 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	free_all(t_minishell *data)
{
	ft_lstclear(&data->env, env_free);
	ft_lstclear(&data->export, env_free);
	free_cmd(data->args);
}
