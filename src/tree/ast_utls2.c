/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utls2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshein <lshein@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:59:47 by lshein            #+#    #+#             */
/*   Updated: 2025/03/06 16:59:49 by lshein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// void	fill_cmd_data_helper()
// {
// 	if (is_only_quotes(command[i]) && count == 1)
// 				node->command[j] = ft_strdup(" ");
// 			else if (is_only_quotes(command[i]) && count > 1 && command[i + 1])
// 				node->command[j] = ft_strdup(" ");
// 			else
// 				node->command[j] = ft_strdup(command[i]);
// }

#include "../../header/minishell.h"

void	fill_cmd_data_helper(t_ast_node *node,
		char *command, int iter[2], int count)
{
	if (is_only_quotes(command) && count == 1)
		node->command[iter[1]] = ft_strdup(" ");
	else if (is_only_quotes(command) && count > 1 && command[iter[0] + 1])
		node->command[iter[1]] = ft_strdup(" ");
	else
		node->command[iter[1]] = ft_strdup(command);
}
