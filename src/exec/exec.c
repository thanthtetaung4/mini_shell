/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 15:27:47 by taung             #+#    #+#             */
/*   Updated: 2025/01/08 06:47:48 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_exec(char **cmd, t_minishell *data)
{
	if (ft_strncmp(cmd[0], "env", ft_strlen("cmd")) == 0)
		print_env(&data->env);
	if (ft_strncmp(cmd[0], "export", ft_strlen("cmd")) == 0)
		ft_export(data, cmd);
	if (ft_strncmp(cmd[0], "unset", ft_strlen("cmd")) == 0)
		ft_unset(data, cmd);
	return (0);
}
