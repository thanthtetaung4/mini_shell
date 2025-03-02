/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 04:15:51 by taung             #+#    #+#             */
/*   Updated: 2025/03/02 16:13:51 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	s = (char *)s;
	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		i--;
	}
	return (0);
}
// int	main()
// {
// 	char str[] = "hello/world/hi";

// 	printf("%s\n",ft_strrchr(str, '/'));
// }
