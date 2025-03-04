/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmd2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshein <lshein@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:55:51 by taung             #+#    #+#             */
/*   Updated: 2025/03/04 14:27:28 by lshein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	remove_cmd_outer_quote(t_minishell *data)
{
	int		i;
	int		str_len;
	char	*tmp;

	i = 0;
	while (data->args[i])
	{
		str_len = ft_strlen(data->args[i]);
		if (data->args[i][0] == '\"' || data->args[i][str_len] == '\"')
		{
			tmp = data->args[i];
			data->args[i] = ft_strtrim(data->args[i], "\"");
			free(tmp);
		}
		else if (data->args[i][0] == '\'' || data->args[i][str_len] == '\'')
		{
			tmp = data->args[i];
			data->args[i] = ft_strtrim(data->args[i], "\'");
			free(tmp);
		}
		i++;
	}
}

int	quote_count(char *input, int option)
{
	int	i;
	int	quote_count;

	i = 0;
	quote_count = 0;
	while (input[i])
	{
		if (input[i] == '\"' && option == 1)
			quote_count++;
		else if (input[i] == '\'' && option == 2)
			quote_count++;
		i++;
	}
	return (quote_count);
}

char	*rm_match_char(char *str, char c)
{
	char	**strs;
	int		i;
	char	*new_str;

	strs = ft_split(str, c);
	free(str);
	str = ft_strdup("");
	i = 0;
	while (strs[i])
	{
		new_str = ft_strjoin(str, strs[i]);
		free(str);
		str = new_str;
		i++;
	}
	free_2d_string(strs);
	return (str);
}

void	remove_cmd_quote(t_minishell *data)
{
	int	i;
	int	s_quote_count;
	int	d_quote_count;

	remove_cmd_outer_quote(data);
	i = 0;
	while (data->args[i])
	{
		s_quote_count = quote_count(data->args[i], 2);
		d_quote_count = quote_count(data->args[i], 1);
		if (s_quote_count > 0 && s_quote_count % 2 == 0)
			data->args[i] = rm_match_char(data->args[i], '\'');
		if (d_quote_count > 0 && d_quote_count % 2 == 0)
			data->args[i] = rm_match_char(data->args[i], '\"');
		i++;
	}
}
