/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 19:31:04 by taung             #+#    #+#             */
/*   Updated: 2024/12/28 22:16:50 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_env	*ft_envnew(char *key, char *value)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(*node));
	if (!(node))
		return (NULL);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

t_env	*ft_envlast(t_env *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_envadd_back(t_env **alst, t_env *new)
{
	t_env	*last;

	if (alst)
	{
		if (*alst)
		{
			last = ft_envlast(*alst);
			last->next = new;
		}
		else
			*alst = new;
	}
}

t_env	*load_env(char **envp)
{
	t_env	*env;
	int		i;
	int		len;
	char	**env_pair;

	len = count_env(envp);
	i = 0;
	env = NULL;
	while (i < len)
	{
		env_pair = env_split(envp[i], '=');
		ft_envadd_back(&env, ft_envnew(env_pair[0], env_pair[1]));
		free(env_pair[0]);
		free(env_pair[1]);
		free(env_pair);
		i++;
	}
	return (env);
}

void	ft_envdelone(t_env *lst, void (*del)(void*))
{
	if (!del)
		return ;
	if (lst)
	{
		(*del)(lst->key);
		(*del)(lst->value);
		free(lst);
	}
}

void	ft_envclear(t_env **lst, void (*del)(void*))
{
	t_env	*tmp;

	if (!del || !lst || !*lst)
		return ;
	while (lst && *lst)
	{
		tmp = (*lst)->next;
		ft_envdelone(*lst, del);
		*lst = tmp;
	}
}
