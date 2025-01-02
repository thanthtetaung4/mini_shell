/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 15:27:47 by taung             #+#    #+#             */
/*   Updated: 2025/01/02 14:38:32 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_exec(char *cmd, t_minishell *data)
{
	if (ft_strncmp(cmd, "env", ft_strlen("cmd")) == 0)
		print_env(&data->env);
	if (ft_strncmp(cmd, "export", ft_strlen("cmd")) == 0)
		print_export_vars(&data->export);
	return (0);
}
