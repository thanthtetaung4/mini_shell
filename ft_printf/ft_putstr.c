/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:56:22 by taung             #+#    #+#             */
/*   Updated: 2024/06/11 22:40:33 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *str);

int	ft_putstr(char *str)
{
	int	count;

	count = 0;
	if (str == NULL)
		return (ft_putstr("(null)"));
	while (*str)
		count += ft_putchar(*str++);
	return (count);
}

// #include <stdio.h>
// int	main(void)
// {
// 	// printf("\n%d\n",ft_putstr("hi"));

// 	printf("------'0.# +' test-----\n\n");
// 	printf("- test: %-10s","hi");
// 	printf("0 test: %010s","hi");
// 	printf(". test: %.2s","hi hello");
// 	printf("# test: %#x", 16);
// 	printf("+ test: \n%+d\n",-19);
// }
