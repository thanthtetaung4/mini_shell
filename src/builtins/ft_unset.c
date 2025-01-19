/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 06:46:44 by taung             #+#    #+#             */
/*   Updated: 2025/01/18 08:00:56 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_lstremove(t_list **lst, int index)
{
	t_list	*current;
	t_list	*prev;
	int		i;

	i = 0;
	current = *lst;
	prev = NULL;
	while (current && i < index)
	{
		prev = current;
		current = current->next;
		i++;
	}
	if (i == index)
	{
		if (prev)
			prev->next = current->next;
		else
			*lst = current->next;
		ft_lstdelone(current, env_free);
	}
}

void	ft_unset(t_minishell *data)
{
	int i;
	int index;

	i = 0;
	while (data->args[++i])
	{
		index = find_var(&(data->export), data->args[i]);
		if (index != -1)
		{
			ft_lstremove(&(data->export), index);
		}
		index = find_var(&(data->env), data->args[i]);
		if (index != -1)
		{
			ft_lstremove(&(data->env), index);
		}
	}
}
