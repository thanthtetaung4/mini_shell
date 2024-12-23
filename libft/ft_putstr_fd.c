/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 01:04:43 by taung             #+#    #+#             */
/*   Updated: 2024/06/01 14:27:08 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	if (s == NULL)
		return ;
	len = 0;
	while (s[len] != '\0')
	{
		len++;
	}
	write(fd, s, len);
}
// #include <fcntl.h> // For open() function

// int main() {
//     int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     if (fd == -1) {
//         return 1; // Handle error
//     }

//     ft_putstr_fd("Hello, World!", fd);

//     close(fd);
//     return 0;
// }
