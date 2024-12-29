/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 19:34:14 by taung             #+#    #+#             */
/*   Updated: 2024/12/29 15:23:25 by taung            ###   ########.fr       */
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

char **allocate_and_copy(char *entry, char *ptr, int len)
{
	char **strs;

	strs = malloc(sizeof(char *) * 2);
	if (!strs)
		return (NULL);
	strs[0] = malloc(len + 1);
	if (!strs[0])
	{
		free(strs);
		return (NULL);
	}
	ft_strncpy(strs[0], entry, len);
	strs[0][len] = '\0';
	ptr++;
	len = ft_strlen(ptr);
	strs[1] = ft_strdup(ptr);
	if (!strs[1])
	{
		free(strs[0]);
		free(strs);
		return (NULL);
	}
	return (strs);
}

char **env_split(char *entry, char c)
{
	char *ptr;
	int len;

	if (!entry)
		return (NULL);
	ptr = ft_strchr(entry, c);
	if (!ptr)
		return (NULL);
	len = ptr - entry;
	return allocate_and_copy(entry, ptr, len);
}

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
