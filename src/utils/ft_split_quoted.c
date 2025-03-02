/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quoted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:15:01 by taung             #+#    #+#             */
/*   Updated: 2025/03/02 16:20:15 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static char	*ft_add_word(size_t start, size_t end, char *s)
{
	size_t	size;
	char	*word;

	size = end - start;
	word = (char *)malloc((size + 1) * sizeof(char));
	if (!word)
		return (NULL);
	ft_memcpy(word, s + start, size);
	word[size] = '\0';
	return (word);
}

void	make_word_helper(char s, int *in_quotes, char *quote_char)
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

static char	*ft_make_word(char *s, char c, size_t *j)
{
	size_t	start;
	size_t	end;
	int		in_quotes;
	char	quote_char;

	while (s[*j] && s[*j] == c)
		(*j)++;
	start = *j;
	in_quotes = 0;
	quote_char = 0;
	while (s[*j])
	{
		if (s[*j] == '\'' || s[*j] == '\"')
		{
			make_word_helper(s[*j], &in_quotes, &quote_char);
		}
		else if (s[*j] == c && !in_quotes)
			break ;
		(*j)++;
	}
	end = *j;
	if (end <= start)
		return (NULL);
	return (ft_add_word(start, end, s));
}

static void	ft_free(char **res, size_t i)
{
	while (i > 0)
	{
		i--;
		free(res[i]);
	}
	free(res);
}

char	**ft_split_quoted(char const *s, char c)
{
	char	**res;
	size_t	size;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	size = ft_word_count((char *)s, c);
	res = (char **)malloc((size + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (i < size)
	{
		res[i] = ft_make_word((char *)s, c, &j);
		if (res[i] == NULL)
		{
			ft_free(res, i);
			return (NULL);
		}
		i++;
	}
	res[size] = NULL;
	return (res);
}
