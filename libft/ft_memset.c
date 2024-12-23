/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:19:01 by taung             #+#    #+#             */
/*   Updated: 2024/06/04 20:37:20 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	void	*res;
	char	*ptr;

	ptr = (char *)s;
	res = s;
	while (n > 0)
	{
		*ptr = c;
		ptr++;
		n--;
	}
	return (res);
}
