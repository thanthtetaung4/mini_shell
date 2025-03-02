/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmd_helper2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:57:32 by taung             #+#    #+#             */
/*   Updated: 2025/03/02 15:58:10 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	init_helper(t_parse_state *state)
{
	state->arg_count = 0;
	state->arg_capacity = 10;
	state->in_single_quote = false;
	state->in_double_quote = false;
	state->error = false;
}
