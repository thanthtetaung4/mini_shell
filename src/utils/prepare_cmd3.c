/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmd3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:33:40 by taung             #+#    #+#             */
/*   Updated: 2025/03/05 20:33:44 by taung            ###   ########.fr       */
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
	int		tab_count;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tab_count = count_tab(input);
	new_input = malloc(sizeof(char) * (ft_strlen(input) - tab_count + 1));
	while(input[i])
	{
		if (input[i] != '\t')
        {
            new_input[j] = input[i];
            j++;
        }
        i++;
	}
	new_input[j] = '\0';
	free(input);
	return (new_input);
}
