/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 08:12:59 by taung             #+#    #+#             */
/*   Updated: 2025/01/19 04:52:14 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_cd(t_minishell *data)
{
	printf("args count: %i\n", data->args_count);
	if (data->args_count == 2)
	{
		if (chdir(data->args[1]) == 1)
		{
			printf("No such file or directory\n");
			return (1);
		}
	}
	else if (data->args_count == 1)
		return (chdir("~"));
	else
	{
		printf("Too many arguements\n");
		return (1);
	}
	return (0);
}
