/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_perm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 09:21:39 by taung             #+#    #+#             */
/*   Updated: 2025/02/23 10:21:49 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include <errno.h>

int	ft_check_perm(char *path)
{
	int ret;

	// printf("path: %s\n", path);
	if(access(path, X_OK) == 0)
		return (0);
	else
	{
		ft_putstr_fd(" Permission denied\n", 2);
		return (1);
	}
}
