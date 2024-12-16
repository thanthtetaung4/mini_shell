/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:20:01 by taung             #+#    #+#             */
/*   Updated: 2024/06/14 18:00:17 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putptr(void *ptr);

int	ft_putptr(void *ptr)
{
	if (ptr == 0)
		return (ft_putstr("(nil)"));
	ft_putstr("0x");
	return (2 + ft_puthex((unsigned long long)ptr));
}

// int	main(void)
// {
// 	int		i;
// 	int *	ptr;

// 	i = 10;

// 	ft_putptr(NULL);
// 	printf("\nprintf: %p\n",NULL);
// 	printf("%#s","hi");
// }
