/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_interpret.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:10:23 by taung             #+#    #+#             */
/*   Updated: 2025/03/07 23:04:46 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

// char	*ft_strndup(const char *src, int len)
// {
// 	char	*result;
// 	int		i;

// 	i = 0;
// 	result = malloc(sizeof(char) * (len + 1));
// 	if (!result)
// 		return (NULL);
// 	while (src && src[i] && i < len)
// 	{
// 		result[i] = src[i];
// 		i++;
// 	}
// 	result[i] = '\0';
// 	return (result);
// }

// char	*ft_strjoinf(char *s1, char *s2, int fs1, int fs2)
// {
// 	char	*result;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	result = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
// 	if (result == NULL)
// 		return (NULL);
// 	while (s1 && s1[i])
// 		result[i++] = s1[j++];
// 	j = 0;
// 	while (s2 && s2[j])
// 		result[i++] = s2[j++];
// 	result[i] = 0;
// 	if (s1 && fs1)
// 		free(s1);
// 	if (s2 && fs2)
// 		free(s2);
// 	return (result);
// }

// int	is_quote(char *q_chars, char c, int *in_quote)
// {
// 	if (!q_chars)
// 		return (0);
// 	if (ft_strchr(q_chars, c))
// 	{
// 		if (!*in_quote)
// 			*in_quote = c;
// 		else if (*in_quote == c)
// 			*in_quote = !*in_quote;
// 	}
// 	return (*in_quote);
// }

// char	*replace_env(char *str, char **result, t_list *envp, int status)
// {
// 	char	*start;
// 	char	*s_value;

// 	start = ++str;
// 	if (*start == '?')
// 	{
// 		s_value = ft_itoa(status);
// 		*result = ft_strjoinf(*result, s_value, 1, 1);
// 		return (++str);
// 	}
// 	while (*str && (ft_isalnum(*str) || *str == '_'))
// 		str++;
// 	start = ft_strndup(start, str - start);
// 	if (start && *start)
// 		*result = ft_strjoinf(*result, get_env_value(envp, start), 1, 1);
// 	else
// 		*result = ft_strcjoin(*result, '$');
// 	if (start)
// 		free(start);
// 	return (str);
// }

// char	*handle_env(char *str, t_list *envp, int status)
// {
// 	char	*result;
// 	int		in_quote;
// 	int		here_doc;

// 	in_quote = 0;
// 	result = NULL;
// 	here_doc = 0;
// 	while (str && *str)
// 	{
// 		if (!is_quote("\'\"", *str, &in_quote) && !ft_strncmp("<<", str, 2))
// 		{
// 			here_doc = 1;
// 			str = result_strcjoin(&result, str);
// 			while (*str && ft_strchr(" \t", *str))
// 				str++;
// 		}
// 		if (here_doc && ft_strchr(" \t", *str))
// 			here_doc = 0;
// 		if (!here_doc && *str == '$' && in_quote != '\'')
// 			str = replace_env(str, &result, envp, status);
// 		else if (*str)
// 			result = ft_strcjoin(result, *str++);
// 	}
// 	return (result);
// }


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
