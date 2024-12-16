/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:22:46 by taung             #+#    #+#             */
/*   Updated: 2024/06/04 20:35:55 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar(int fd, char c);
void	ft_putnbr(int nb, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	ft_putnbr(n, fd);
}

void	ft_putnbr(int nb, int fd)
{
	if (nb == -2147483648)
	{
		ft_putchar(fd, '-');
		ft_putchar(fd, '2');
		nb = 147483648;
	}
	if (nb < 0)
	{
		ft_putchar(fd, '-');
		nb *= -1;
	}
	if (nb >= 10)
	{
		ft_putnbr(nb / 10, fd);
		ft_putnbr(nb % 10, fd);
	}
	else
	{
		ft_putchar(fd, nb + '0');
	}
}

void	ft_putchar(int fd, char c)
{
	write(fd, &c, 1);
}
// #include <fcntl.h>

// int main() {
//     int fd = open("output-number.txt", O_RDWR | O_CREAT, 0777);
//     if (fd == -1) {
//         return (1);
//     }

//     ft_putnbr_fd(-1, fd);

//     close(fd);
//     return (0);
// }
