/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 07:15:04 by taung             #+#    #+#             */
/*   Updated: 2025/03/03 15:01:06 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	export_add_var(t_minishell *data, char *key, char *value)
{
	if (!data->export)
	{
		data->export = ft_envnew(key, value);
		ft_update_env(&(data->env), ft_envnew(key, value));
		return ;
	}
	if (find_var(&data->export, key) != -1)
	{
		update_export_var(data, value, find_var(&data->export, key));
		ft_update_env(&(data->env), ft_envnew(key, value));
		return ;
	}
	else
	{
		add_var(data, ft_envnew(key, value));
		ft_add_env(&(data->env), ft_envnew(key, value));
		return ;
	}
}

int	handle_invalid_identifier(char **key_value, int *is_print)
{
	if (*is_print == 0)
	{
		ft_putstr_fd(" not a valid identifier\n", 2);
		*is_print = 1;
	}
	free(key_value[0]);
	free(key_value[1]);
	free(key_value);
	return (1);
}

int	process_key_value(t_minishell *data, char **key_value, int *is_print)
{
	if (is_valid_var(key_value[0]) == 0)
		return (handle_invalid_identifier(key_value, is_print));
	export_add_var(data, key_value[0], key_value[1]);
	free(key_value[0]);
	free(key_value[1]);
	free(key_value);
	return (0);
}

int	handle_export_command(t_minishell *data, t_ast_node *node, int *is_print)
{
	int		i;
	char	**key_value;
	int		status;

	i = 0;
	status = 0;
	while (node->command[++i])
	{
		if (ft_strchr(node->command[i], '='))
		{
			key_value = key_value_splitter(node->command[i], '=');
			status = process_key_value(data, key_value, is_print);
			if (status == 1)
				return (1);
		}
		else
		{
			key_value = key_value_splitter(node->command[i], '=');
			status = process_key_value2(data, key_value, is_print);
		}
	}
	return (status);
}

int	ft_export(t_minishell *data, t_ast_node *node)
{
	int	is_print;

	is_print = 0;
	if (!node->command[1])
	{
		print_export_vars(&data->export);
		return (0);
	}
	return (handle_export_command(data, node, &is_print));
}
