/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:41:25 by taung             #+#    #+#             */
/*   Updated: 2025/03/06 07:19:07 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	handle_cd_error(char *pwd, const char *message)
{
	ft_putstr_fd((char *)message, 2);
	free(pwd);
	return (1);
}

void	update_prev_dir(t_minishell *data, char *prev_dir)
{
	char	*val;

	(void)prev_dir;
	val = get_env_value(data->env, "PWD");
	export_add_var(data, "OLDPWD", val);
	free(val);
}

void	update_env_pwd(t_minishell *data)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	export_add_var(data, "PWD", pwd);
	free(pwd);
}
