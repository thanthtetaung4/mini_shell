/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_interpret.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:10:23 by taung             #+#    #+#             */
/*   Updated: 2025/01/22 07:37:38 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*get_value_before_dollar(char *cmd, char *found_dollar)
{
	char	*before_dollar;

	before_dollar = ft_substr(cmd, 0, found_dollar - cmd);
	return (before_dollar);
}

char	*get_value(t_list *env, char *found_dollar, char **pos)
{
	int		i;
	char	*value;
	char	*key;

	i = 1;
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
char	*interpret(char **cmd, t_list *env, char *found_dollar)
{
	char	*before_dollar;
	char	*after_dollar;
	char	*value;
	char	*pos;
	char	*tmp;

	while ((found_dollar = ft_strchr(*cmd, '$')))
	{
		tmp = *cmd;
		pos = found_dollar;
		before_dollar = get_value_before_dollar(*cmd, found_dollar);
		value = get_value(env, found_dollar, &pos);
		after_dollar = get_value_after_variable(*cmd, pos);
		*cmd = ft_strjoin(before_dollar, value);
		free(value);
		free(before_dollar);
		free(tmp);
		tmp = *cmd;
		*cmd = ft_strjoin(*cmd, after_dollar);
		free(tmp);
		free(after_dollar);
	}
	return (*cmd);
}

void	ft_interpret(t_minishell *data)
{
	int		i;
	char	*found_dollar;

	i = 0;
	while (data->args[i])
	{
		// printf("cmd: %s\n", data->args[i]);
		found_dollar = ft_strchr(data->args[i], '$');
		if (found_dollar != 0)
		{
			if (ft_strchr(found_dollar, '\''))
			{
				i++;
				continue ;
			}
			// printf("found dollar: %s\n", found_dollar);
			interpret(&data->args[i], data->env, found_dollar);
			// printf("arg: %s\n", data->args[i]);
		}
		i++;
	}
	return ;
}
