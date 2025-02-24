/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 08:43:04 by taung             #+#    #+#             */
/*   Updated: 2025/02/23 02:24:06 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_count_tds(char **str)
{
	int	i;

	i = 0;
	if (str[i] == NULL)
		return (0);
	while(str[i] != NULL)
	{
		i++;
	}
	return (i);
}

// int main(void)
// {
// 	char *str[] = {"hi", "hello", NULL};

// 	printf("%i\n", ft_count_tds(str));
// }
