/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 07:07:31 by taung             #+#    #+#             */
/*   Updated: 2025/01/18 07:18:15 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_pwd(void)
{
	char	*buffer;

	buffer = NULL;
	buffer = getcwd(buffer, 0);
	if (!buffer)
	{
		printf("error\n");
		free(buffer);
		return (1);
	}
	ft_putstr_fd(buffer, 1);
	ft_putstr_fd("\n", 1);
	free(buffer);
	return (0);
}
