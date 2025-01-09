/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 15:16:34 by taung             #+#    #+#             */
/*   Updated: 2025/01/03 05:53:01 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_list	*load_env(char **envp)
{
	t_list	*env;
	int		i;
	int		len;
	char	**env_pair;

	len = count_env(envp);
	i = 0;
	env = NULL;
	while (i < len)
	{
		env_pair = key_value_splitter(envp[i], '=');
		ft_lstadd_back(&env, ft_envnew(env_pair[0], env_pair[1]));
		free(env_pair[0]);
		free(env_pair[1]);
		free(env_pair);
		i++;
	}
	return (env);
}
