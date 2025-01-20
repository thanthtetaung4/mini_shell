/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 07:15:04 by taung             #+#    #+#             */
/*   Updated: 2025/01/18 08:00:40 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	export_add_var(t_minishell *data, char *key, char *value)
{
	t_list	*current_export;

	if (!data->export)
	{
		data->export = ft_envnew(key, value);
		return;
	}
	replace_with_env_value(data, &value);
	if (find_var(&data->export, key) != -1)
	{
		update_export_var(data, value, find_var(&data->export, key));
		ft_update_env(&(data->env), ft_envnew(key, value));
		return;
	}
	else
	{
		add_var(data, ft_envnew(key, value));
		ft_add_env(&(data->env), ft_envnew(key, value));
		return;
	}
}

void	ft_export(t_minishell *data)
{
	int		i;
	t_list	*new_node;
	char**	key_value;
	int		is_print;

	is_print = 0;
	i = 0;
	if (!data->args[1])
	{
		print_export_vars(&data->export);
		return;
	}
	while (data->args[++i])
	{
		// remove_quotes(&args[i]);
		key_value = key_value_splitter(data->args[i], '=');
		if (is_valid_var(key_value[0]) == 0)
		{
			if (is_print == 0)
				printf("minishell: export: `%s': not a valid identifier\n", key_value[0]);
			is_print = 1;
			free(key_value);
			continue;
		}
		export_add_var(data, key_value[0], key_value[1]);
		free(key_value);
	}
}
