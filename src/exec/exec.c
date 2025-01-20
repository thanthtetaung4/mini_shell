/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 15:27:47 by taung             #+#    #+#             */
/*   Updated: 2025/01/20 09:16:40 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_exec(t_minishell *data)
{
	if (ft_strncmp(data->args[0], "env", ft_strlen(data->args[0])) == 0)
		print_env(&data->env);
	if (ft_strncmp(data->args[0], "export", ft_strlen(data->args[0])) == 0)
		ft_export(data);
	if (ft_strncmp(data->args[0], "unset", ft_strlen(data->args[0])) == 0)
		ft_unset(data);
	if (ft_strncmp(data->args[0], "exit", ft_strlen(data->args[0])) == 0)
		ft_exit(data);
	if (ft_strncmp(data->args[0], "pwd", ft_strlen(data->args[0])) == 0)
		ft_pwd();
	if (ft_strncmp(data->args[0], "cd", ft_strlen(data->args[0])) == 0)
		ft_cd(data);
	if (ft_strncmp(data->args[0], "echo", ft_strlen(data->args[0])) == 0)
		ft_echo(data);
	return (0);
}
