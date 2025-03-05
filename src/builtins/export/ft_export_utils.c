/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 21:25:20 by taung             #+#    #+#             */
/*   Updated: 2025/03/05 21:25:22 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../header/minishell.h"

int	process_key_value2(t_minishell *data, char **key_value, int *is_print)
{
	if (is_valid_var(key_value[0]) == 0)
		return (handle_invalid_identifier(key_value, is_print));
	export_add_var2(data, key_value[0], key_value[1]);
	free(key_value[0]);
	free(key_value[1]);
	free(key_value);
	return (0);
}

void	export_add_var2(t_minishell *data, char *key, char *value)
{
	if (!data->export)
	{
		data->export = ft_envnew(key, value);
		return ;
	}
	if (find_var(&data->export, key) != -1)
	{
		update_export_var(data, value, find_var(&data->export, key));
		return ;
	}
	else
	{
		add_var(data, ft_envnew(key, value));
		return ;
	}
}
