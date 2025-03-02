/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmd_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:57:14 by taung             #+#    #+#             */
/*   Updated: 2025/03/02 15:58:06 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

// Initialize parsing state
t_parse_state	*init_parse_state(const char *input)
{
	t_parse_state	*state;

	state = malloc(sizeof(t_parse_state));
	if (!state)
	{
		perror("malloc failed");
		return (NULL);
	}
	init_helper(state);
	state->buffer = strdup(input);
	if (!state->buffer)
	{
		perror("strdup failed");
		free(state);
		return (NULL);
	}
	state->args = malloc(state->arg_capacity * sizeof(char *));
	if (!state->args)
	{
		perror("malloc failed");
		free(state->buffer);
		free(state);
		return (NULL);
	}
	return (state);
}

// Clean up resources used by parse state
void	cleanup_parse_state(t_parse_state *state)
{
	int	i;

	if (!state)
		return ;
	if (state->buffer)
	{
		free(state->buffer);
	}
	if (state->args)
	{
		i = 0;
		while (i < state->arg_count)
		{
			free(state->args[i]);
			i++;
		}
		free(state->args);
	}
	free(state);
}

// Resize arguments array when capacity is reached
bool	resize_args_array(t_parse_state *state)
{
	int		new_capacity;
	char	**new_args;
	int		i;

	new_capacity = state->arg_capacity * 2;
	new_args = malloc(new_capacity * sizeof(char *));
	if (!new_args)
	{
		perror("malloc failed");
		return (false);
	}
	i = 0;
	while (i < state->arg_count)
	{
		new_args[i] = state->args[i];
		i++;
	}
	free(state->args);
	state->args = new_args;
	state->arg_capacity = new_capacity;
	return (true);
}

// Skip spaces in the input string
char	*skip_spaces(char *ptr)
{
	while (*ptr == ' ')
		ptr++;
	return (ptr);
}

// Handle quotes in parsing
void	handle_quote(char c, t_parse_state *state)
{
	if (c == '\'' && !state->in_double_quote)
	{
		state->in_single_quote = !state->in_single_quote;
	}
	else if (c == '\"' && !state->in_single_quote)
	{
		state->in_double_quote = !state->in_double_quote;
	}
}
