/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:47:13 by taung             #+#    #+#             */
/*   Updated: 2025/03/02 15:59:14 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

// Check if current character should end the argument
bool	is_arg_end(char c, t_parse_state *state)
{
	return (c == ' ' && !state->in_single_quote && !state->in_double_quote);
}

// Parse a single argument from the input string
char	*parse_argument(char **ptr, t_parse_state *state)
{
	char	*token_start;
	char	*arg;
	char	*arg_ptr;

	token_start = *ptr;
	arg = malloc(ft_strlen(token_start) + 1);
	if (!arg)
	{
		state->error = true;
		return (NULL);
	}
	arg_ptr = arg;
	while (**ptr)
	{
		if (is_arg_end(**ptr, state))
			break ;
		handle_quote(**ptr, state);
		*arg_ptr = **ptr;
		arg_ptr++;
		(*ptr)++;
	}
	*arg_ptr = '\0';
	if (**ptr)
		(*ptr)++;
	return (arg);
}

// Validate quotes and handle errors
bool	validate_quotes(t_parse_state *state)
{
	if (state->in_single_quote || state->in_double_quote)
	{
		printf("Error: Mismatched quotes\n");
		return (false);
	}
	return (true);
}

// Process a single argument
bool	process_argument(char **ptr, t_parse_state *state)
{
	char	*arg;

	arg = parse_argument(ptr, state);
	if (state->error || !arg)
	{
		if (arg)
			free(arg);
		return (false);
	}
	if (!validate_quotes(state))
	{
		free(arg);
		return (false);
	}
	if (state->arg_count >= state->arg_capacity)
	{
		if (!resize_args_array(state))
		{
			free(arg);
			return (false);
		}
	}
	state->args[state->arg_count] = arg;
	state->arg_count++;
	return (true);
}

// Main function to split arguments
char	**split_args(const char *input)
{
	t_parse_state	*state;
	char			*ptr;
	char			**result;

	state = init_parse_state(input);
	if (!state)
		return (NULL);
	ptr = state->buffer;
	while (*ptr)
	{
		ptr = skip_spaces(ptr);
		if (*ptr == '\0')
			break ;
		if (!process_argument(&ptr, state))
		{
			cleanup_parse_state(state);
			return (NULL);
		}
	}
	result = state->args;
	result[state->arg_count] = NULL;
	state->args = NULL;
	cleanup_parse_state(state);
	return (result);
}
