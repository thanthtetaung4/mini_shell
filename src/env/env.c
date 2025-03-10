/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 19:31:04 by taung             #+#    #+#             */
/*   Updated: 2025/03/02 15:44:51 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_list	*ft_envnew(char *key, char *value)
{
	t_list	*node;
	t_env	*env_node;

	node = (t_list *)malloc(sizeof(*node));
	if (!(node))
		return (NULL);
	env_node = (t_env *)malloc(sizeof(*env_node));
	if (!(env_node))
		return (NULL);
	env_node->key = ft_strdup(key);
	env_node->value = ft_strdup(value);
	node->content = env_node;
	node->next = NULL;
	return (node);
}

void	ft_add_env(t_list **env, t_list *new_node)
{
	if (new_node)
		ft_lstadd_back(env, new_node);
	else
	{
		free(((t_env *)new_node->content)->key);
		free(((t_env *)new_node->content)->value);
		free(new_node->content);
		free(new_node);
	}
}

void	ft_update_env(t_list **env, t_list *new_node)
{
	t_list	*current;
	t_list	*prev;

	current = *env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(((t_env *)current->content)->key,
				((t_env *)new_node->content)->key) == 0)
		{
			if (prev)
				prev->next = new_node;
			else
				*env = new_node;
			new_node->next = current->next;
			free(((t_env *)current->content)->key);
			free(((t_env *)current->content)->value);
			free(current->content);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
	ft_add_env(env, new_node);
}
