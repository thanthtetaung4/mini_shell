/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 19:34:14 by taung             #+#    #+#             */
/*   Updated: 2024/12/28 22:20:57 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "string.h"

// return the number of env entries
int	count_env(char **env)
{
	int n;
	int i;

	i = 0;
	n = 0;
	while(env[i])
	{
		n++;
		i++;
	}
	return (n);
}
// return the index of the first occurrence of char | -1
// int	strnchr(char *str, char c)
// {
// 	int	i;

// 	i = 0;
// 	while(str[i])
// 	{
// 		if (str[i] == c)
// 			return i;
// 		i++;
// 	}
// 	return (-1);
// }

char **env_split(char *entry, char c)
{
	char **strs;
	int i;
	int len;
	char *ptr;

	if (!entry)
		return (NULL);
	strs = malloc(sizeof(char *) * 2);
	if (!strs)
		return (NULL);
	ptr = ft_strchr(entry, c);
	if (!ptr)
	{
		free(strs);
		return (NULL);
	}
	len = ptr - entry;
	strs[0] = malloc(len + 1);
	if (!strs[0])
	{
		free(strs);
		return (NULL);
	}
	strncpy(strs[0], entry, len);
	strs[0][len] = '\0';
	ptr++;
	len = ft_strlen(ptr);
	strs[1] = malloc(len + 1);
	if (!strs[1])
	{
		free(strs[0]);
		free(strs);
		return (NULL);
	}
	// strcpy(strs[1], ptr);
	strs[1] = ft_strdup(ptr);
	return (strs);
}

// void	map(char *entry, char **key, char **value)
// {
// 	char **entry_pair;

// 	entry_pair = env_split(entry, '=');
// 	*key = ft_strdup(entry_pair[0]);
// 	*value = ft_strdup(entry_pair[1]);
// 	free (entry_pair[0]);
// 	free (entry_pair[1]);
// 	free (entry_pair);
// }

void	print_env(t_env **env)
{
	t_env	*current;

	current = *env;
	while(current)
	{
		printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return;
}

// int	main(int argc, char **argv, char **envp)
// {
// 	char	*key;
// 	char	*value;

// 	printf("%d\n",count_env(envp));
// 	get_key_value(envp[0], key, value);
// 	printf("env => %s\n",envp[0]);
// 	printf("key: %s\n value: %s\n",key, value);
// }
