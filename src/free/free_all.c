/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 15:31:26 by taung             #+#    #+#             */
/*   Updated: 2025/01/08 06:36:01 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	free_all(t_minishell *data, char **cmd)
{
	ft_lstclear(&data->env, env_free);
	ft_lstclear(&data->export, env_free);
	free_cmd(cmd);
}
