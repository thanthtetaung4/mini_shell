/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 07:14:05 by taung             #+#    #+#             */
/*   Updated: 2025/03/10 21:08:13 by taung            ###   ########.fr       */
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
			return ;
		}
		current = current->next;
		index--;
	}
	return ;
}

char	*extract_key(char *str)
{
	char	*replace_str;

	replace_str = ft_strchr(str, '$');
	if (!replace_str)
		return (NULL);
	return (ft_strdup(replace_str + 1));
}

char	*get_env_value(t_list *env, char *key)
{
	t_list	*current;

	current = env;
	while (current)
	{
		if (ft_strcmp(((t_env *)current->content)->key, key) == 0)
			return (ft_strdup(((t_env *)current->content)->value));
		current = current->next;
	}
	return (ft_strdup(""));
}
