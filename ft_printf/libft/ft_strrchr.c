/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:52:29 by taung             #+#    #+#             */
/*   Updated: 2024/06/04 20:23:53 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*res;

	res = 0;
	if ((char)c == '\0')
	{
		res = &((char *)s)[ft_strlen(s)];
	}
	while (*s != '\0')
	{
		if (*s == (char)c)
			res = (char *)s;
		s = s + 1;
	}
	return (res);
}
