/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:52:00 by taung             #+#    #+#             */
/*   Updated: 2024/06/14 18:40:06 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	ft_puthex(unsigned long long numb);

int	ft_puthex(unsigned long long numb)
{
	int	count;

	count = 0;
	if (numb >= 16)
	{
		count += ft_puthex(numb / 16);
		count += ft_puthex(numb % 16);
	}
	else
	{
		if (numb > 9)
			count += ft_putchar('a' + numb - 10);
		else
			count += ft_putchar(numb + '0');
	}
	return (count);
}

// #include <stdio.h>

// int main()
// {
// 	int i = -10;
// 	// printf("%p\n",&i);

// 	printf("\n%d\n",ft_puthex((unsigned int)i));
// 	printf("\n%d\n",ft_puthex(i));
// }
