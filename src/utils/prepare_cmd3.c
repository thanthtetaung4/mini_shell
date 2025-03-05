/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmd3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:33:40 by taung             #+#    #+#             */
/*   Updated: 2025/03/06 00:26:36 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	count_tab(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while(input[i])
	{
		if (input[i] == '\t')
			count++;
		i++;
	}
	return (count);
}

char *ft_remove_tabs(char *input)
{
	char	*new_input;
	int		i;

	i = 0;
	new_input = malloc(sizeof(char) * (ft_strlen(input) + 1));
	while(input[i])
	{
		if (input[i] == '\t')
            new_input[i] = ' ';
		else
			new_input[i] = input[i];
        i++;
	}
	new_input[i] = '\0';
	free(input);
	return (new_input);
}
