/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_empty_args.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:54:30 by taung             #+#    #+#             */
/*   Updated: 2025/03/02 15:54:36 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	empty_args_count(char **args)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (ft_strlen(args[i]) == 0)
			count++;
		i++;
	}
	return (count);
}

void	remove_empty_args(t_minishell *data)
{
	int		i;
	int		count;
	char	**new_args;

	i = 0;
	count = empty_args_count(data->args);
	new_args = malloc(sizeof(char *) * (data->args_count - count + 1));
	if (!new_args)
		return ;
	i = 0;
	count = 0;
	while (data->args[i])
	{
		if (ft_strlen(data->args[i]) != 0)
		{
			new_args[i - count] = ft_strdup(data->args[i]);
		}
		else
			count++;
		i++;
	}
	new_args[i - count] = NULL;
	free_2d_string(data->args);
	data->args = new_args;
	data->args_count = data->args_count - count;
}
