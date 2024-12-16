/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:21:41 by taung             #+#    #+#             */
/*   Updated: 2024/06/03 13:45:04 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c >= 32 && c < 127)
		return (1);
	return (0);
}
// #include <stdio.h>
// int	main()
// {
// 	if(ft_isprint('c') > 0)
// 		printf("Printable\n");
// 	else
// 		printf("NOT Printable\n");
// }
