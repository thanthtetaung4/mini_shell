/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 01:04:43 by taung             #+#    #+#             */
/*   Updated: 2024/06/03 12:23:38 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t	len;

	if (s == NULL)
		return ;
	len = ft_strlen(s);
	write(fd, s, len);
	write(fd, "\n", 1);
}
// #include <fcntl.h>

// int main() {
//     int fd = open("output-123.txt", O_RDWR | O_CREAT, 0777);
//     if (fd == -1) {
//         return 1;
//     }

//     ft_putendl_fd("Hello, World!", fd);

//     close(fd);
//     return 0;
// }
