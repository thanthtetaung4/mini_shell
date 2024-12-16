/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:42:56 by taung             #+#    #+#             */
/*   Updated: 2024/06/11 23:23:00 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int numb);

int	ft_putnbr(int numb)
{
	char	*str;
	int		count;

	str = ft_itoa(numb);
	count = ft_putstr(str);
	free(str);
	return (count);
}

// #include <limits.h>
// int	main(void)
// {
// 	unsigned int	i;

// 	i = UINT_MAX;
// 	ft_putnbr(i);
// }
