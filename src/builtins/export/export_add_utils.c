/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 07:14:05 by taung             #+#    #+#             */
/*   Updated: 2025/01/09 09:40:44 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	update_export_var(t_minishell *data, char *value, int index)
{
	t_list	*current;

	current = data->export;
	while (index >= 0)
	{
		if (index == 0)
		{
			free(((t_env *)current->content)->value);
			((t_env *)current->content)->value = ft_strdup(value);
			return;
		}
		current = current->next;
		index--;
	}
	return;
}

