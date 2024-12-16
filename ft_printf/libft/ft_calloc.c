/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:33:51 by taung             #+#    #+#             */
/*   Updated: 2024/06/04 20:42:06 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*res;
	unsigned int	i;

	i = count * size;
	res = malloc(count * size);
	if (res == NULL)
		return (NULL);
	ft_bzero(res, i);
	return (res);
}
// int main()
// {
// 	char *str = "This is a test string";
// 	int arr[10] = {1,2,3,4,5,6,7,8,9,0};

// 	char *str2 = calloc(strlen(str)+1, sizeof(char));
// 	char *arr2 = calloc(10, sizeof(int));

// 	printf("%p,%d\n",arr2,arr2[0]);

// }
