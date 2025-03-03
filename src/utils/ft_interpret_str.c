/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_interpret_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:10:23 by taung             #+#    #+#             */
/*   Updated: 2025/03/03 13:37:24 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*get_value_str(t_minishell *data, t_list *env, char *found_dollar,
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
	while (ft_isalnum(found_dollar[i]) == 1 && found_dollar[i] != '\0')
		i++;
	key = ft_substr(found_dollar + 1, 0, i - 1);
	*pos += i;
	value = get_env_value(env, key);
	free(key);
	return (value);
}

char	*get_value_after_variable_str(char *cmd, char *pos)
{
	char	*after_dollar;

	after_dollar = ft_substr(cmd, pos - cmd, ft_strlen(cmd) - (pos - cmd));
	return (after_dollar);
}

/**
 * Helper function to check if the variable after $ sign is valid
 */
static int	is_valid_variable(char *found_dollar)
{
	if (ft_strlen(found_dollar) == 1)
		return (0);
	if ((ft_isalnum(found_dollar[1]) == 0 && found_dollar[1] != '?'))
		return (0);
	return (1);
}

/**
 * Helper function to expand a single variable occurrence
 */
static char	*expand_variable(t_minishell *data, char *result,
		char *found_dollar)
{
	t_interpret	*interpret;
	char		*new_result;

	interpret = malloc(sizeof(t_interpret));
	interpret->pos = found_dollar;
	interpret->before_dollar = get_value_before_dollar_str(result,
			found_dollar);
	interpret->value = get_value_str(data, data->env, found_dollar,
			&(interpret->pos));
	interpret->after_dollar = get_value_after_variable_str(result,
			interpret->pos);
	interpret->tmp = ft_strjoin(interpret->before_dollar, interpret->value);
	new_result = ft_strjoin(interpret->tmp, interpret->after_dollar);
	free(interpret->value);
	free(interpret->before_dollar);
	free(interpret->after_dollar);
	free(interpret->tmp);
	free(interpret);
	return (new_result);
}

/**
 * Main function to interpret and expand environment variables in a string
 */
char	*ft_interpret_str(t_minishell *data, char *line)
{
	char	*found_dollar;
	char	*result;
	char	*tmp;

	if (!line)
		return (NULL);
	result = ft_strdup(line);
	found_dollar = ft_strchr(result, '$');
	while (found_dollar)
	{
		if (!is_valid_variable(found_dollar))
			break ;
		tmp = result;
		result = expand_variable(data, result, found_dollar);
		free(tmp);
		found_dollar = ft_strchr(result, '$');
	}
	return (result);
}
