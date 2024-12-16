/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:33:48 by taung             #+#    #+#             */
/*   Updated: 2024/06/04 21:12:41 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_word_count(char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			while (s[i + 1] != c && s[i + 1])
				i++;
			count++;
			i++;
		}
	}
	return (count);
}

static char	*ft_add_word(size_t start, size_t end, char *s)
{
	size_t	size;
	char	*word;

	word = NULL;
	size = end - start;
	word = (char *)malloc((size + 1) * sizeof(char));
	if (!word)
		return (NULL);
	ft_strlcpy(word, s, size + 1);
	return (word);
}

static void	*ft_make_word(char *s, char c, size_t *j)
{
	size_t	start;
	size_t	end;

	start = 0;
	end = 0;
	while (s[*j])
	{
		if (s[*j] == c)
			(*j)++;
		else
		{
			start = *j;
			while (s[*j] && s[*j] != c)
				(*j)++;
			end = *j;
			return (ft_add_word(0, end - start, s + start));
		}
	}
	return (NULL);
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

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	size;
	size_t	i;
	size_t	j;

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
