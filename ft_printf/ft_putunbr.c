/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:07:43 by taung             #+#    #+#             */
/*   Updated: 2024/06/11 23:27:44 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_uitoa(unsigned int n);
static int	ft_uintlen(unsigned int n);
int			ft_putunbr(unsigned int numb);

static int	ft_uintlen(unsigned int n)
{
	int	len;

	len = 0;
	if (n < 0)
		len++;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char	*ft_uitoa(unsigned int n)
{
	char			*str;
	int				len;
	unsigned int	num;

	len = ft_uintlen(n);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	if (n == 0)
		str[0] = '0';
	str[len] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		num = -n;
	}
	else
		num = n;
	while (num != 0)
	{
		str[len - 1] = (num % 10) + '0';
		num = num / 10;
		len--;
	}
	return (str);
}

int	ft_putunbr(unsigned int numb)
{
	char	*str;
	int		count;

	str = ft_uitoa(numb);
	count = ft_putstr(str);
	free(str);
	return (count);
}

// #include <limits.h>
// int	main(void)
// {
// 	unsigned int	i;

// 	i = UINT_MAX;
// 	ft_putunbr(i);
// }
