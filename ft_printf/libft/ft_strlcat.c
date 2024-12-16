/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:42:14 by taung             #+#    #+#             */
/*   Updated: 2024/06/03 16:35:59 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size);

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;

	i = 0;
	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if ((size - 1) > dest_len && size > 0)
	{
		while (src[i] && dest_len + i < size - 1)
		{
			dst[dest_len + i] = src[i];
			i++;
		}
		dst[dest_len + i] = '\0';
	}
	if (dest_len >= size)
		dest_len = size;
	return (dest_len + src_len);
}
// int main()
// {
// 	// ft_strlcat test
// 	printf("\n---------ft_strlcat---------\n");
// 	char dest2[10] = "asdf";
// 	char *src2 = "jkl";
// 	printf("my-res: %li\n", ft_strlcat(dest2, src2, 6));
// 	printf("dest: %s, dest-addr: %p\n",dest2, &dest2);
// 	printf("src: %s, src-addr: %p\n",src2, &src2);
// 	printf("---------ft_strlcat---------\n");
// }
