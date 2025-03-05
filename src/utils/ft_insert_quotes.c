/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:51:12 by taung             #+#    #+#             */
/*   Updated: 2025/03/04 19:12:18 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	count_pnr(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
		{
			count++;
			if ((input[i] == '<' || input[i] == '>') && input[i
					+ 1] == input[i])
				i++;
		}
		i++;
	}
	return (count);
}

void	handle_quotes_state(char c, int *in_d_quotes, int *in_s_quotes)
{
	if (c == '"' && !*in_s_quotes)
		*in_d_quotes = !*in_d_quotes;
	else if (c == '\'' && !*in_d_quotes)
		*in_s_quotes = !*in_s_quotes;
}

void	handle_special_char(char *input, int *i, char *new_input, int *j)
{
	new_input[(*j)++] = ' ';
	new_input[(*j)++] = input[*i];
	if ((input[*i] == '>' || input[*i] == '<') && input[*i + 1] == input[*i])
		new_input[(*j)++] = input[++(*i)];
	new_input[(*j)++] = ' ';
	(*i)++;
}

char	*ft_insert_spaces(char *input)
{
	int		i;
	int		j;
	int		in_d_quotes;
	int		in_s_quotes;
	char	*new_input;

	i = 0;
	j = 0;
	in_d_quotes = 0;
	in_s_quotes = 0;
	// printf("%d",ft_strlen(input) + (count_pnr(input) * 2) + 1);
	new_input = malloc(ft_strlen(input) + (count_pnr(input) * 2) + 1);
	if (!new_input)
		return (NULL);
	while (input[i])
	{
		handle_quotes_state(input[i], &in_d_quotes, &in_s_quotes);
		if ((input[i] == '|' || input[i] == '>' || input[i] == '<')
			&& !in_d_quotes && !in_s_quotes)
			handle_special_char(input, &i, new_input, &j);
		else
			new_input[j++] = input[i++];
	}
	new_input[j] = '\0';
	free(input);
	return (new_input);
}
