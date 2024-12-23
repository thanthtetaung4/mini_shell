/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:59:09 by taung             #+#    #+#             */
/*   Updated: 2024/06/04 20:32:28 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*temp;
	int		i;

	temp = (char *)src;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (dest > src)
	{
		i = (int)n;
		while (--i >= 0)
			((char *)dest)[i] = temp[i];
	}
	else
	{
		i = -1;
		while (++i < (int)n)
			((char *)dest)[i] = temp[i];
	}
	return (dest);
}
