/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_interpret.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshein <lshein@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:10:23 by taung             #+#    #+#             */
/*   Updated: 2025/03/06 02:10:37 by lshein           ###   ########.fr       */
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

	found_dollar = ft_strchr(*cmd, '$');
	while (found_dollar)
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
		found_dollar = ft_strchr(*cmd, '$');
	}
	return (*cmd);
}

void	ft_should_interpret(t_minishell *data, t_ast_node *node, int i,
		char *found_dollar)
{
	int	cmd_count;

	cmd_count = ft_count_tds(node->command);
	if (found_dollar && (ft_strlen(found_dollar) == 1 || (found_dollar[1] != '?'
				&& found_dollar[1] != '_' && ft_isalnum(found_dollar[1]) == 0)))
	{
		return ;
	}
	if (cmd_count > 1 && i > 0)
	{
		if (found_dollar != 0 && ft_strcmp(node->command[i - 1], "<<") != 0)
		{
			if (ft_strchr(found_dollar, '\''))
			{
				return ;
			}
			interpret(data, &node->command[i], data->env, found_dollar);
		}
		return ;
	}
	interpret(data, &node->command[i], data->env, found_dollar);
}

void	ft_interpret(t_minishell *data, t_ast_node *node)
{
	int		i;
	char	*found_dollar;

	i = 0;
	while (node->command[i])
	{
		found_dollar = ft_strchr(node->command[i], '$');
		ft_should_interpret(data, node, i, found_dollar);
		i++;
	}
}
