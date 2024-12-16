/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:27:51 by taung             #+#    #+#             */
/*   Updated: 2024/06/11 23:16:23 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

int	ft_write_conversion(va_list args, char specifier);
int	ft_printf(const char *str, ...);

int	ft_write_conversion(va_list args, char specifier)
{
	if (specifier == 'd')
		return (ft_putnbr(va_arg(args, int)));
	else if (specifier == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (specifier == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (specifier == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (specifier == 'x')
		return (ft_puthex(va_arg(args, unsigned int)));
	else if (specifier == 'X')
		return (ft_puthexc(va_arg(args, unsigned int)));
	else if (specifier == 'u')
		return (ft_putunbr(va_arg(args, unsigned int)));
	else if (specifier == '%')
		return (ft_putchar('%'));
	else if (specifier == 'p')
		return (ft_putptr(va_arg(args, void *)));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int		char_written;
	va_list	args;

	va_start(args, str);
	char_written = 0;
	while (*str)
	{
		if (*str == '%')
		{
			char_written += ft_write_conversion(args, *(++str));
			str++;
		}
		else
			char_written += ft_putchar(*str++);
	}
	return (char_written);
}

// int main()
// {
// 	ft_printf("this is %c\n",'A');
// }
