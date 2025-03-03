/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_interpret_str_util.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:36:36 by taung             #+#    #+#             */
/*   Updated: 2025/03/03 13:37:02 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*get_value_before_dollar_str(char *cmd, char *found_dollar)
{
	char *before_dollar;

	if (found_dollar - cmd <= 0)
		return (ft_strdup(""));
	before_dollar = ft_substr(cmd, 0, found_dollar - cmd);
	return (before_dollar);
}
