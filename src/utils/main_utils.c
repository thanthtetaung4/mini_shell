/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshein <lshein@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:52:05 by lshein            #+#    #+#             */
/*   Updated: 2025/03/06 03:05:39 by lshein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*remove_trailing_whitespace(const char* str)
{
	int	i;

    if (str == NULL)
	return NULL;
    size_t len = strlen(str);
    int lastNonWhitespace = -1;
	i = len - 1;
	while (i >= 0)
	{
		if (str[i] != ' ' && str[i] != '\t')
		{
			lastNonWhitespace = i;
			break;
		}
		i--;
	}
	if (lastNonWhitespace == -1)
	{
		char* result = malloc(1);
		if (result == NULL) {
			return NULL;
		}
		result[0] = '\0';
		return result;
	}
	char* result = malloc(lastNonWhitespace + 2);
	if (result == NULL)
		return NULL;
	strncpy(result, str, lastNonWhitespace + 1);
	result[lastNonWhitespace + 1] = '\0';
	return result;
}

int	check_syntax_errors(char *input)
{
	int	len;
	char	*tmp;
	int i;

	i = 0;
	tmp = remove_trailing_whitespace(input);
	len = ft_strlen(tmp);
	while (tmp[i])
	{
		if ((tmp[i] == '>' && tmp[i + 1] == '<') || (tmp[i] == '<' && tmp[i + 1] == '>'))
		{
			ft_putstr_fd("minishell: syntax error near unexpected redir token'\n",
				2);
			free(tmp);
			return (0);
		}
		i++;
	}
	if ((tmp[len - 1] == '>' || tmp[len - 1] == '<'))
	{
		ft_putstr_fd("minishell: syntax error near unexpected redir token'\n",
			2);
		free(tmp);
		return (0);
	}
	if (tmp[0] == '|' || tmp[len - 1] == '|')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		free(tmp);
		return (0);
	}
	free(tmp);
	return (1);
}

void	init_count_quotes(int *s_quote_count, int *d_quote_count,
		int *in_d_quotes, int *in_s_quotes)
{
	*s_quote_count = 0;
	*d_quote_count = 0;
	*in_d_quotes = 0;
	*in_s_quotes = 0;
}

int	print_err(int *s_quote_count, int *d_quote_count)
{
	if ((*s_quote_count) % 2 != 0)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `' || \"\n",
			2);
		return (0);
	}
	if ((*d_quote_count) % 2 != 0)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `\"\n", 2);
		return (0);
	}
	return (1);
}

int	count_quotes(char *input)
{
	int	s_quote_count;
	int	d_quote_count;
	int	i;
	int	in_d_quotes;
	int	in_s_quotes;

	i = -1;
	init_count_quotes(&s_quote_count, &d_quote_count, &in_d_quotes,
		&in_s_quotes);
	while (input[++i])
	{
		if (input[i] == '"' && !in_s_quotes)
		{
			d_quote_count++;
			in_d_quotes = !in_d_quotes;
		}
		if (input[i] == '\'' && !in_d_quotes)
		{
			s_quote_count++;
			in_s_quotes = !in_s_quotes;
		}
	}
	return (print_err(&s_quote_count, &d_quote_count));
}
