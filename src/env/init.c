/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 15:16:34 by taung             #+#    #+#             */
/*   Updated: 2024/12/29 15:16:43 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

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
