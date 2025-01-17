/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 07:14:05 by taung             #+#    #+#             */
/*   Updated: 2025/01/17 09:22:03 by taung            ###   ########.fr       */
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
char	*extract_key(char *str)
{
	char	*replace_str;

	replace_str = ft_strchr(str, '$');
		if (!replace_str)
			return NULL;
	return (ft_strdup(replace_str + 1));
}

char *get_value_before_dollar(char *str)
{
	char	*replace_str;
	char	*value;

	replace_str = ft_strchr(str, '$');
	if (!replace_str)
		return (ft_strdup(str));
	value = ft_substr(str, 0, replace_str - str);
	return (value);
}

char *get_env_value(t_list *env, char *key)
{
	t_list	*current;

	current = env;
	while (current)
	{
		if (ft_strcmp(((t_env *)current->content)->key, key) == 0)
			return (ft_strdup(((t_env *)current->content)->value));
		current = current->next;
	}
	return (NULL);
}

void	replace_with_env_value(t_minishell *data, char **value)
{
	char	*before_dollar;
	char	*env_value;

	remove_quotes(value);
	if ((*value)[0] != '\'' && ft_strchr(*value, '$') != 0)
	{
		printf("getting val before $\n");
		before_dollar = get_value_before_dollar(*value);
		printf("before dollar: %s\n", before_dollar);
		printf("getting env value\n");
		env_value = (get_env_value(data->env, extract_key(*value)));
		printf("env value %s\n", env_value);
		free(*value);
		*value = ft_strjoin(before_dollar, env_value);
		free(before_dollar);
		free(env_value);
	}
}

