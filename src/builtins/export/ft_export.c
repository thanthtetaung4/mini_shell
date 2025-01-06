/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 06:42:35 by codespace         #+#    #+#             */
/*   Updated: 2025/01/06 07:16:11 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	export_add_var(t_minishell *data, t_list *new_node)
{
	t_list	*current_export;

	if (!data->export)
	{
		data->export = new_node;
		return;
	}
	if (find_export_var(data, ((t_env *)new_node->content)->key) != -1)
	{
		update_export_var(data, ((t_env *)new_node->content)->value, find_export_var(data, ((t_env *)new_node->content)->key));
		ft_update_env(&(data->env), new_node);
		return;
	}
	else
	{
		add_var(data, new_node);
		ft_add_env(&(data->env),new_node);
		return;
	}
}

void	ft_export(t_minishell *data, char **args)
{
	int		i;
	t_list	*new_node;
	char**	key_value;
	int		is_print;

	is_print = 0;
	i = 0;
	if (!args[1])
	{
		print_export_vars(&data->export);
		return;
	}
	while (args[++i])
	{
		key_value = key_value_splitter(args[i], '=');
		if (is_valid_var(key_value[0]) == 0)
		{
			if (is_print == 0)
				printf("minishell: export: `%s': not a valid identifier\n", key_value[0]);
			is_print = 1;
			free(key_value);
			continue;
		}
		new_node = ft_envnew(key_value[0], key_value[1]);
		export_add_var(data, new_node);

		free(key_value);
	}
}
