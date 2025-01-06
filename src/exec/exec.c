/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 15:27:47 by taung             #+#    #+#             */
/*   Updated: 2025/01/03 06:01:59 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_exec(char **cmd, t_minishell *data)
{
	if (ft_strncmp(cmd[0], "env", ft_strlen("cmd")) == 0)
		print_env(&data->env);
	if (ft_strncmp(cmd[0], "export", ft_strlen("cmd")) == 0)
		ft_export(data, cmd);
	return (0);
}
