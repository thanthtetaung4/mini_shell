/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshein <lshein@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:03:20 by lshein            #+#    #+#             */
/*   Updated: 2025/03/06 17:55:20 by lshein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	status_change(t_minishell *data)
{
	if (g_sig_status)
		data->status = 130;
	if (data->input == NULL)
		handle_eof(data);
}

char	*allocate_result(int size)
{
	char	*result;

	result = malloc(size);
	if (result == NULL)
		return (NULL);
	result[0] = '\0';
	return (result);
}

int	find_last_non_whitespace(const char *str, int len)
{
	int	i;

	i = len - 1;
	while (i >= 0)
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (i);
		i--;
	}
	return (-1);
}

char	*remove_trailing_whitespace(const char *str)
{
	int		last_non_whitespace;
	size_t	len;
	char	*result;

	if (str == NULL)
		return (NULL);
	len = strlen(str);
	last_non_whitespace = find_last_non_whitespace(str, len);
	if (last_non_whitespace == -1)
		return (allocate_result(1));
	result = allocate_result(last_non_whitespace + 2);
	if (result == NULL)
		return (NULL);
	strncpy(result, str, last_non_whitespace + 1);
	result[last_non_whitespace + 1] = '\0';
	return (result);
}
