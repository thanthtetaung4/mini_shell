/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quoted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 07:16:36 by taung             #+#    #+#             */
/*   Updated: 2025/01/21 07:16:54 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../header/minishell.h"

// static size_t	ft_word_count(char *s, char c)
// {
// 	size_t	i;
// 	size_t	count;
// 	int		in_quotes;

// 	i = 0;
// 	count = 0;
// 	in_quotes = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == '\'' || s[i] == '\"')
// 			in_quotes = !in_quotes;
// 		if (s[i] == c && !in_quotes)
// 			i++;
// 		else
// 		{
// 			while (s[i] && (s[i] != c || in_quotes))
// 			{
// 				if (s[i] == '\'' || s[i] == '\"')
// 					in_quotes = !in_quotes;
// 				i++;
// 			}
// 			count++;
// 		}
// 	}
// 	return (count);
// }

// static char	*ft_add_word(size_t start, size_t end, char *s)
// {
// 	size_t	size;
// 	char	*word;

// 	word = NULL;
// 	size = end - start;
// 	word = (char *)malloc((size + 1) * sizeof(char));
// 	if (!word)
// 		return (NULL);
// 	ft_strlcpy(word, s, size + 1);
// 	return (word);
// }

// static void	*ft_make_word(char *s, char c, size_t *j)
// {
// 	size_t	start;
// 	size_t	end;
// 	int		in_quotes;

// 	start = 0;
// 	end = 0;
// 	in_quotes = 0;
// 	while (s[*j])
// 	{
// 		if (s[*j] == c && !in_quotes)
// 			(*j)++;
// 		else
// 		{
// 			start = *j;
// 			while (s[*j] && (s[*j] != c || in_quotes))
// 			{
// 				if (s[*j] == '\'' || s[*j] == '\"')
// 					in_quotes = !in_quotes;
// 				(*j)++;
// 			}
// 			end = *j;
// 			return (ft_add_word(0, end - start, s + start));
// 		}
// 	}
// 	return (NULL);
// }

// static void	ft_free(char **res, size_t i)
// {
// 	while (i > 0)
// 	{
// 		i--;
// 		free(res[i]);
// 	}
// 	free(res);
// }

// char	**ft_split_quoted(char const *s, char c)
// {
// 	char	**res;
// 	size_t	size;
// 	size_t	i;
// 	size_t	j;

// 	i = 0;
// 	j = 0;
// 	size = ft_word_count((char *)s, c);
// 	res = (char **)malloc((size + 1) * sizeof(char *));
// 	if (!res)
// 		return (NULL);
// 	while (i < size)
// 	{
// 		res[i] = ft_make_word((char *)s, c, &j);
// 		if (res[i] == NULL)
// 		{
// 			ft_free(res, i);
// 			return (NULL);
// 		}
// 		i++;
// 	}
// 	res[size] = NULL;
// 	return (res);
// }

#include "../../header/minishell.h"

static size_t	ft_word_count(char *s, char c)
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
				if ((s[i] == '\'' || s[i] == '\"'))
				{
					if (!in_quotes)
					{
						in_quotes = 1;
						quote_char = s[i];
					}
					else if (s[i] == quote_char)
					{
						in_quotes = 0;
						quote_char = 0;
					}
				}
				i++;
			}
		}
	}
	return (count);
}

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
			if (!in_quotes)
			{
				in_quotes = 1;
				quote_char = s[*j];
			}
			else if (s[*j] == quote_char)
			{
				in_quotes = 0;
				quote_char = 0;
			}
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
