/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quoted_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:16:09 by taung             #+#    #+#             */
/*   Updated: 2025/03/02 16:21:54 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	wrod_count_helper(char s, int *in_quotes, char *quote_char)
{
	if ((s == '\'' || s == '\"'))
	{
		if (!*in_quotes)
		{
			*in_quotes = 1;
			*quote_char = s;
		}
		else if (s == *quote_char)
		{
			*in_quotes = 0;
			*quote_char = 0;
		}
	}
}

size_t	ft_word_count(char *s, char c)
{
	size_t	i;
	size_t	count;
	int		in_quotes;
	char	quote_char;

	i = 0;
	count = 0;
	in_quotes = 0;
	quote_char = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c && !in_quotes)
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && (s[i] != c || in_quotes))
			{
				wrod_count_helper(s[i], &in_quotes, &quote_char);
				i++;
			}
		}
	}
	return (count);
}
