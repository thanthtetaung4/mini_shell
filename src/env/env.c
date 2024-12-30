/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 19:31:04 by taung             #+#    #+#             */
/*   Updated: 2024/12/30 21:50:24 by taung            ###   ########.fr       */
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
