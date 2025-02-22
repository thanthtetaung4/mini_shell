/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 06:34:35 by taung             #+#    #+#             */
/*   Updated: 2025/02/23 01:27:42 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_print_args(char **args)
{
	int	i;

	i = 0;
	while(args[i])
	{
		if (i == 0)
			printf("cmd: %s\n",args[i]);
		else
			printf("arg[%d]: %s\n",i,args[i]);
		printf("size: %ld\n", ft_strlen(args[i]));
		i++;
	}
}
