#include "../../header/minishell.h"

int	count_pnr(char *input)
{
	int	i = 0;
	int	count = 0;

	while (input[i])
	{
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
		{
			count++;
			if ((input[i] == '<' || input[i] == '>') && input[i + 1] == input[i])
				i++;
		}
		i++;
	}
	return (count);
}


void handle_quotes_state(char c, int *in_d_quotes, int *in_s_quotes)
{
    if (c == '"' && !*in_s_quotes)
        *in_d_quotes = !*in_d_quotes;
    else if (c == '\'' && !*in_d_quotes)
        *in_s_quotes = !*in_s_quotes;
}

void handle_special_char(char *input, int *i, char *new_input, int *j)
{
    new_input[(*j)++] = ' ';
    new_input[(*j)++] = input[*i];

    if ((input[*i] == '>' || input[*i] == '<') && input[*i + 1] == input[*i])
        new_input[(*j)++] = input[++(*i)];

    new_input[(*j)++] = ' ';
    (*i)++;
}

char *ft_insert_spaces(char *input)
{
    int i = 0;
    int j = 0;
    int in_d_quotes = 0;
    int in_s_quotes = 0;
    char *new_input;

    new_input = malloc(ft_strlen(input) + (count_pnr(input) * 2) + 1);
    if (!new_input)
        return (NULL);

    while (input[i])
    {
        handle_quotes_state(input[i], &in_d_quotes, &in_s_quotes);

        if ((input[i] == '|' || input[i] == '>' || input[i] == '<') && !in_d_quotes && !in_s_quotes)
            handle_special_char(input, &i, new_input, &j);
        else
            new_input[j++] = input[i++];
    }

    new_input[j] = '\0';
    free(input);
    return (new_input);
}

void    init_helper(t_parse_state *state)
{
    state->arg_count = 0;
    state->arg_capacity = 10;
    state->in_single_quote = false;
    state->in_double_quote = false;
    state->error = false;
}
// Initialize parsing state
t_parse_state *init_parse_state(const char *input)
{
    t_parse_state *state;

    state = malloc(sizeof(t_parse_state));
    if (!state)
    {
        perror("malloc failed");
        return NULL;
    }
    init_helper(state);
    state->buffer = strdup(input);
    if (!state->buffer)
    {
        perror("strdup failed");
        free(state);
        return NULL;
    }
    state->args = malloc(state->arg_capacity * sizeof(char *));
    if (!state->args)
    {
        perror("malloc failed");
        free(state->buffer);
        free(state);
        return NULL;
    }
    return state;
}

// Clean up resources used by parse state
void cleanup_parse_state(t_parse_state *state)
{
    int i;

    if (!state)
        return;
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
bool resize_args_array(t_parse_state *state)
{
    int new_capacity;
    char **new_args;
    int i;

    new_capacity = state->arg_capacity * 2;
    new_args = malloc(new_capacity * sizeof(char *));
    if (!new_args)
    {
        perror("malloc failed");
        return false;
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
    return true;
}

// Skip spaces in the input string
char *skip_spaces(char *ptr)
{
    while (*ptr == ' ') ptr++;
    return ptr;
}

// Handle quotes in parsing
void handle_quote(char c, t_parse_state *state)
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

// Check if current character should end the argument
bool is_arg_end(char c, t_parse_state *state)
{
    return c == ' ' && !state->in_single_quote && !state->in_double_quote;
}

// Parse a single argument from the input string
char *parse_argument(char **ptr, t_parse_state *state)
{
    char *token_start;
    char *arg;
    char *arg_ptr;

    token_start = *ptr;
    arg = malloc(strlen(token_start) + 1);
    if (!arg)
    {
        perror("malloc failed");
        state->error = true;
        return NULL;
    }
    arg_ptr = arg;
    while (**ptr)
    {
        if (is_arg_end(**ptr, state))
            break;
        handle_quote(**ptr, state);
        *arg_ptr = **ptr;
        arg_ptr++;
        (*ptr)++;
    }
    *arg_ptr = '\0';
    if (**ptr) (*ptr)++;
    return arg;
}

// Validate quotes and handle errors
bool validate_quotes(t_parse_state *state)
{
    if (state->in_single_quote || state->in_double_quote) {
        printf("Error: Mismatched quotes\n");
        return false;
    }
    return true;
}

// Process a single argument
bool process_argument(char **ptr, t_parse_state *state)
{
    char *arg;

    arg = parse_argument(ptr, state);
    if (state->error || !arg)
    {
        if (arg) free(arg);
        return false;
    }
    if (!validate_quotes(state))
    {
        free(arg);
        return false;
    }
    if (state->arg_count >= state->arg_capacity)
    {
        if (!resize_args_array(state))
        {
            free(arg);
            return false;
        }
    }
    state->args[state->arg_count] = arg;
    state->arg_count++;
    return true;
}

// Main function to split arguments
char **split_args(const char *input)
{
    t_parse_state *state;
    char *ptr;
    char **result;

    state = init_parse_state(input);
    if (!state)
    {
        return NULL;
    }
    ptr = state->buffer;
    while (*ptr)
    {
        ptr = skip_spaces(ptr);
        if (*ptr == '\0') break;
        if (!process_argument(&ptr, state))
        {
            cleanup_parse_state(state);
            return NULL;
        }
    }
    result = state->args;
    result[state->arg_count] = NULL; // Null-terminate the args array
    state->args = NULL;     // Detach args from state so they're not freed
    cleanup_parse_state(state);
    return result;
}

void remove_cmd_outer_quote(t_minishell *data)
{
	int	i;
	int	str_len;

	i = 0;
	while (data->args[i])
	{
		str_len = ft_strlen(data->args[i]);
		if (data->args[i][0] == '\"' || data->args[i][str_len] == '\"')
		{
			data->args[i] = ft_strtrim(data->args[i], "\"");
		}
		else if (data->args[i][0] == '\'' || data->args[i][str_len] == '\'')
		{
			data->args[i] = ft_strtrim(data->args[i], "\'");
		}
		// printf("args: %s\n", data->args[i]);
		i++;
	}
}
int		quote_count(char *input, int option)
{
	int		i;
	int quote_count;

	i = 0;
	quote_count = 0;
	while (input[i])
	{
		if (input[i] == '\"' && option == 1)
			quote_count++;
		else if (input[i] == '\'' && option == 2)
			quote_count++;
		i++;
	}
	return (quote_count);
}

char *rm_match_char(char *str, char c)
{
	char **strs;
	int i;
	char	*new_str;

	strs = ft_split(str, c);
	free(str);
	str = ft_strdup("");
	i = 0;
	while(strs[i])
	{
		new_str = ft_strjoin(str, strs[i]);
		free(str);
		str = new_str;
		i++;
	}
	free_2d_string(strs);
	return (str);
}
void	remove_cmd_quote(t_minishell *data)
{
	int	i;
	int s_quote_count;
	int d_quote_count;
	char *new_arg;

	remove_cmd_outer_quote(data);
	i = 0;
	// printf("%s\n", data->input);
	while (data->args[i])
	{
		s_quote_count = quote_count(data->args[i], 2);
		d_quote_count = quote_count(data->args[i], 1);
		// printf("s_quote_count: %d\n", s_quote_count);
		// printf("d_quote_count: %d\n", d_quote_count);
		if (s_quote_count > 0 && s_quote_count % 2 == 0)
			data->args[i] = rm_match_char(data->args[i], '\'');
		if (d_quote_count > 0 && d_quote_count % 2 == 0)
			data->args[i] = rm_match_char(data->args[i], '\"');
		i++;
	}
	// ft_print_args(data->args);
}

int empty_args_count(char **args)
{
    int	i;
    int	count;

    i = 0;
    count = 0;
    while (args[i])
    {
        if (ft_strlen(args[i]) == 0)
            count++;
        i++;
    }
    return (count);
}

void    remove_empty_args(t_minishell *data)
{
    int	i;
    int	count;
    char	**new_args;

    i = 0;
    count = empty_args_count(data->args);
    new_args = malloc(sizeof(char *) * (data->args_count - count + 1));
    if (!new_args)
        return ;
    i = 0;
    count = 0;
    while (data->args[i])
    {
        if (ft_strlen(data->args[i]) != 0)
        {
            new_args[i - count] = ft_strdup(data->args[i]);
        }
        else
            count++;
        i++;
    }
    new_args[i - count] = NULL;
    free_2d_string(data->args);
    data->args = new_args;
    data->args_count = data->args_count - count;
}
