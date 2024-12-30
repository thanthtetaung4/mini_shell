/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 15:27:47 by taung             #+#    #+#             */
/*   Updated: 2024/12/30 22:14:05 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_exec(char *cmd, t_list **env)
{
	if (ft_strncmp(cmd, "env", ft_strlen("cmd")) == 0)
		print_env(env);
	return (0);
}
