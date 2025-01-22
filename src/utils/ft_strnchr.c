/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:50:02 by taung             #+#    #+#             */
/*   Updated: 2025/01/20 11:08:09 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_strnchr(char *str, int n, int c)
{
	int	i;

	i = 0;
	while (i < n && str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
