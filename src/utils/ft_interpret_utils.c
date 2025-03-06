/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_interpret_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshein <lshein@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:02:52 by taung             #+#    #+#             */
/*   Updated: 2025/03/06 17:46:47 by lshein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*get_value_before_dollar(char *cmd, char *found_dollar)
{
	char	*before_dollar;

	if (found_dollar - cmd <= 0)
		return (ft_strdup(""));
	before_dollar = ft_substr(cmd, 0, found_dollar - cmd);
	return (before_dollar);
}

char	*get_value(t_minishell *data, t_list *env, char *found_dollar,
		char **pos)
{
	int		i;
	char	*value;
	char	*key;

	i = 1;
	if (found_dollar[i] == '?')
	{
		*pos += 2;
		return (ft_itoa(data->status));
	}
	if (found_dollar[i] == '_')
	{
		*pos += 2;
		return (get_env_value(env, "_"));
	}
	while (ft_isalnum(found_dollar[i]) == 1 && found_dollar[i] != '\0')
		i++;
	key = ft_substr(found_dollar + 1, 0, i - 1);
	*pos += i;
	value = get_env_value(env, key);
	free(key);
	return (value);
}

char	*get_value_after_variable(char *cmd, char *pos)
{
	char	*after_dollar;

	after_dollar = ft_substr(cmd, pos - cmd, ft_strlen(cmd) - (pos - cmd));
	return (after_dollar);
}

char	*ft_strcjoin(char *str, char c)
{
	char	*result;
	int		char_len;
	int		i;

	char_len = 2;
	if (c == '\0')
		char_len = 1;
	result = malloc(sizeof(char) * (ft_strlen(str) + char_len));
	i = 0;
	while (str && str[i])
	{
		result[i] = str[i];
		i++;
	}
	if (c)
		result[i++] = c;
	result[i] = '\0';
	if (str)
		free(str);
	return (result);
}

char	*result_strcjoin(char **result, char *str)
{
	*result = ft_strcjoin(*result, *str++);
	*result = ft_strcjoin(*result, *str++);
	return (str);
}
