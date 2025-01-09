/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 21:58:40 by taung             #+#    #+#             */
/*   Updated: 2025/01/08 07:36:05 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	env_free(void *env)
{
	if (((t_env *)env)->key)
		free(((t_env *)env)->key);
	if (((t_env *)env)->value)
		free(((t_env *)env)->value);
	free(env);
}
