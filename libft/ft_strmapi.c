/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 21:40:53 by taung             #+#    #+#             */
/*   Updated: 2024/06/03 13:20:49 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*res;

	res = malloc(ft_strlen(s) + 1 * sizeof(char));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s))
	{
		res[i] = f(i, s[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}

// char	example_function(unsigned int index, char c)
// {
// 	if (c >= 'a' && c <= 'z')
// 		return (c - 32);
// 	return (c);
// }
// int main() {
//     char const *s = "hello, world!";
//     char *result = ft_strmapi(s, example_function);
//     if (result != NULL) {
//         printf("Result: %s\n", result);
//         free(result);
//     } else {
//         printf("Memory allocation failed.\n");
//     }
//     return 0;
// }
