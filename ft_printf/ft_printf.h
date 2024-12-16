/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 22:49:29 by taung             #+#    #+#             */
/*   Updated: 2024/06/11 23:02:17 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>

int	ft_putchar(char c);

int	ft_putstr(char *str);

int	ft_putnbr(int numb);

int	ft_puthex(unsigned long long numb);

int	ft_puthexc(unsigned long long numb);

int	ft_putptr(void *ptr);

int	ft_putunbr(unsigned int numb);

int	ft_printf(const char *str, ...);

#endif
