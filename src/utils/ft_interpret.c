/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_interpret.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:10:23 by taung             #+#    #+#             */
/*   Updated: 2025/03/03 13:44:00 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*interpret(t_minishell *data, char **cmd, t_list *env,
		char *found_dollar)
{
	char	*before_dollar;
	char	*after_dollar;
	char	*value;
	char	*pos;
	char	*tmp;

	while ((found_dollar = ft_strchr(*cmd, '$')))
	while ((found_dollar = ft_strchr(*cmd, '$')))
	{
		tmp = *cmd;
		pos = found_dollar;
		before_dollar = get_value_before_dollar(*cmd, found_dollar);
		value = get_value(data, env, found_dollar, &pos);
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

void	ft_should_interpret(t_minishell *data, int i, char *found_dollar)
{
	if (found_dollar && (ft_strlen(found_dollar) == 1
			|| (ft_isalnum(found_dollar[1]) == 0 && found_dollar[1] != '?')))
	{
		return ;
	}
	if (data->args_count > 1 && i > 0)
	{
		if (found_dollar != 0 && ft_strcmp(data->args[i - 1], "<<") != 0)
		{
			if (ft_strchr(found_dollar, '\''))
			{
				return ;
			}
			interpret(data, &data->args[i], data->env, found_dollar);
		}
		return ;
	if (data->args_count > 1 && i > 0)
	{
		if (found_dollar != 0 && ft_strcmp(data->args[i - 1], "<<") != 0)
		{
			if (ft_strchr(found_dollar, '\''))
			{
				return ;
			}
			interpret(data, &data->args[i], data->env, found_dollar);
		}
		return ;
	}
	interpret(data, &data->args[i], data->env, found_dollar);
}
}

void	ft_interpret(t_minishell *data)
{
	int		i;
	char	*found_dollar;

	i = 0;
	while (data->args[i])
	{
		found_dollar = ft_strchr(data->args[i], '$');
		ft_should_interpret(data, i, found_dollar);
		i++;
	}
}
