/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:26:32 by taung             #+#    #+#             */
/*   Updated: 2025/03/02 15:36:45 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	print_export_vars(t_list **export)
{
	t_list	*current;

	current = *export;
	while (current)
	{
		if (((t_env *)current->content)->value[0] == '\''
			|| ((t_env *)current->content)->value[0] == '\"')
			printf("%s=%s\n", ((t_env *)current->content)->key,
				((t_env *)current->content)->value);
		else
			printf("%s=\"%s\"\n", ((t_env *)current->content)->key,
				((t_env *)current->content)->value);
		current = current->next;
	}
	return ;
}

int	find_var(t_list **list, char *key)
{
	t_list	*current;
	int		i;

	i = 0;
	current = *list;
	while (current && current->content)
	{
		if (ft_strcmp(key, ((t_env *)current->content)->key) == 0)
		{
			return (i);
		}
		current = current->next;
		i++;
	}
	return (-1);
}

int	is_valid_var(char *key)
{
	int	i;

	i = 0;
	if (ft_isalpha(key[i]) || key[i] == '_' || key[i] == 34 || key[i] == 39)
	{
		i++;
		while (key[i])
		{
			if (ft_isalnum(key[i]) || key[i] == '_' || key[i] == 34
				|| key[i] == 39)
				i++;
			else
				return (0);
		}
		return (1);
	}
	return (0);
}
