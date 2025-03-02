/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 06:09:05 by taung             #+#    #+#             */
/*   Updated: 2025/03/02 16:12:42 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	remove_quotes_export(t_minishell *data)
{
	int		i;
	int		j;
	int		z;
	char	*new_str;

	z = 0;
	while (data->args[z])
	{
		i = 0;
		j = 0;
		new_str = malloc(sizeof(char) * (ft_strlen(data->args[z]) + 1));
		while ((data->args)[z][i])
		{
			if ((data->args)[z][i] != '\"' && (data->args)[z][i] != '\'')
			{
				new_str[j] = (data->args)[z][i];
				j++;
			}
			i++;
		}
		new_str[j] = '\0';
		free((data->args)[z]);
		(data->args)[z] = new_str;
		z++;
	}
}
