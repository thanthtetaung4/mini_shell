/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 21:13:57 by taung             #+#    #+#             */
/*   Updated: 2024/06/04 20:37:02 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (n > 0)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
		n--;
	}
	return (dest);
}

// int main()
// {
// 	printf("---------ft_memcpy---------\n");

// 	char src[] = "Hello";
// 	char dest[] = "";
// 	char *c_res = (char*)memcpy(dest,src,4);
// 	printf("src:%s\nc-res:%s\ndest:%s\n", src,c_res,dest);
// 	printf("dest-len: %zu, src-len: %zu\n",strlen(dest),strlen(src));

// 	printf("res-addr:  %p\ndest-addr: %p\n", memcpy(dest,src,5),dest);

// 	printf("---------------------------\n");
// }
