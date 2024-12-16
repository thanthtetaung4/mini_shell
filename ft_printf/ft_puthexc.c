/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:52:00 by taung             #+#    #+#             */
/*   Updated: 2024/06/11 22:40:15 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	ft_puthexc(unsigned long long numb);

int	ft_puthexc(unsigned long long numb)
{
	int	count;

	count = 0;
	if (numb >= 16)
	{
		count += ft_puthexc(numb / 16);
		count += ft_puthexc(numb % 16);
	}
	else
	{
		if (numb > 9)
			count += ft_putchar('A' + numb - 10);
		else
			count += ft_putchar(numb + '0');
	}
	return (count);
}

// // #include <stdio.h>

// int main()
// {
// 	int i = -10;
// 	printf("%p\n",&i);

// 	printf("\n%d\n",ft_puthexc((unsigned int)i));
// }
