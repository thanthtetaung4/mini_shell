/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 22:05:37 by taung             #+#    #+#             */
/*   Updated: 2024/06/04 20:18:39 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*));

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(s))
	{
		f (i, s + i);
		i++;
	}
}
// void	example_func(unsigned int i, char* s)
// {
// 	if (s[i] >= 'a' && s[i] <= 'z')
// 		s[i] = s[i] - 32;
// }
// int	main(void)
// {
// 	char* str = "Hello this is 42SG";
// 	printf("str: %s\n",str);
// 	ft_striteri(str, example_func);
// 	printf("str: %s\n",str);
// }
