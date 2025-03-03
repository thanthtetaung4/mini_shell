/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_interpret.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:10:23 by taung             #+#    #+#             */
/*   Updated: 2025/02/28 00:50:05 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

extern int	g_sig_status;

char	*get_value_before_dollar_str(char *cmd, char *found_dollar)
{
	char	*before_dollar;

	if (found_dollar - cmd <= 0)
		return (ft_strdup(""));
	before_dollar = ft_substr(cmd, 0, found_dollar - cmd);
	return (before_dollar);
}

char	*get_value_str(t_minishell *data, t_list *env, char *found_dollar, char **pos)
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
static int is_valid_variable(char *found_dollar)
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
static char *expand_variable(t_minishell *data, char *result, char *found_dollar)
{
    char *before_dollar;
    char *after_dollar;
    char *value;
    char *pos;
    char *tmp;
    char *new_result;

    pos = found_dollar;
    before_dollar = get_value_before_dollar_str(result, found_dollar);
    value = get_value_str(data, data->env, found_dollar, &pos);
    after_dollar = get_value_after_variable_str(result, pos);

    tmp = ft_strjoin(before_dollar, value);
    new_result = ft_strjoin(tmp, after_dollar);

    free(value);
    free(before_dollar);
    free(after_dollar);
    free(tmp);

    return (new_result);
}

/**
 * Main function to interpret and expand environment variables in a string
 */
char *ft_interpret_str(t_minishell *data, char *line)
{
    char *found_dollar;
    char *result;
    char *tmp;

    if (!line)
        return (NULL);

    result = ft_strdup(line);
    found_dollar = ft_strchr(result, '$');
    while (found_dollar)
    {
        if (!is_valid_variable(found_dollar))
            break;

        tmp = result;
        result = expand_variable(data, result, found_dollar);
        free(tmp);
        found_dollar = ft_strchr(result, '$');
    }
    return (result);
}
