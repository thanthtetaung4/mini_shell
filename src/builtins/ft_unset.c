/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 06:46:44 by taung             #+#    #+#             */
/*   Updated: 2025/01/08 17:16:22 by taung            ###   ########.fr       */
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
		printf("skipping %s\n", ((t_env *)current->content)->key);
		current = current->next;
		i++;
	}
	if (i == index)
	{
		if (prev)
			prev->next = current->next;
		else
			*lst = current->next;
		printf("unsetting key: %s, value: %s\n",((t_env *)current->content)->key,((t_env *)current->content)->value);
		ft_lstdelone(current, env_free);
		printf("OK\n");
	}
}

void	ft_unset(t_minishell *data, char **args)
{
	int i;
	int index;

	i = 0;
	while (args[++i])
	{
		printf("Unsetting %s\n", args[i]);
		index = find_var(&(data->export), args[i]);
		if (index != -1)
		{
			printf("export unsetting\n");
			ft_lstremove(&(data->export), index);
		}
		printf("export unset\n");
		index = find_var(&(data->env), args[i]);
		if (index != -1)
		{
			printf("env unsetting\n");
			ft_lstremove(&(data->env), index);
		}

		// Figure out why env is seg faulting even thought it's not touched
	}
}
