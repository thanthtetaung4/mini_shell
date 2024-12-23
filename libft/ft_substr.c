/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:08:47 by taung             #+#    #+#             */
/*   Updated: 2024/06/04 20:38:36 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	j;

	if (len >= ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	if (start >= ft_strlen(s))
		len = 0;
	res = malloc((len + 1) * (sizeof(char)));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len && s[i])
	{
		if (j >= start)
			res[i++] = s[j];
		j++;
	}
	res[i] = '\0';
	return (res);
}
