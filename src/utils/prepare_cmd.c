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


char	*ft_insert_spaces(char *input)
{
    int		i;
    int		j;
    int		count;
    int		in_d_quotes;
    int		in_s_quotes;
    char	*new_input;

    count = count_pnr(input);
    i = 0;
    j = 0;
    in_d_quotes = 0;
    in_s_quotes = 0;
    new_input = malloc(ft_strlen(input) + (count * 2) + 1);
    if (!new_input)
        return (NULL);
    while (input[i])
    {
        if (input[i] == '"' && !in_s_quotes)
            in_d_quotes = !in_d_quotes;
        else if (input[i] == '\'' && !in_d_quotes)
            in_s_quotes = !in_s_quotes;

        if ((input[i] == '|' || input[i] == '>' || input[i] == '<') && !in_d_quotes && !in_s_quotes)
        {
            new_input[j++] = ' ';
            new_input[j++] = input[i];
            if ((input[i] == '>' || input[i] == '<') && input[i + 1] == input[i])
                new_input[j++] = input[++i];
            new_input[j++] = ' ';
            i++;
        }
        else
            new_input[j++] = input[i++];
    }
    new_input[j] = '\0';
    free(input);
    return (new_input);
}

char **split_args(const char *input) {
    char **args;
    int arg_count = 0;
    int arg_capacity = 10;
    char *buffer = strdup(input); // Make a mutable copy
    if (!buffer) {
        perror("strdup failed");
        return NULL;
    }

    args = malloc(arg_capacity * sizeof(char *));
    if (!args) {
        perror("malloc failed");
        free(buffer);
        return NULL;
    }

    char *ptr = buffer;
    bool in_single_quote = false, in_double_quote = false;

    while (*ptr) {
        while (*ptr == ' ') ptr++;  // Skip leading spaces
        if (*ptr == '\0') break;    // End of input

        char *token_start = ptr;
        char *arg = malloc(strlen(ptr) + 1);  // Allocate memory for argument
        if (!arg) {
            perror("malloc failed");
            free(buffer);
            free(args);
            return NULL;
        }

        char *arg_ptr = arg;

        while (*ptr) {
            if (*ptr == '\'' && !in_double_quote) {
                in_single_quote = !in_single_quote;
            } else if (*ptr == '\"' && !in_single_quote) {
                in_double_quote = !in_double_quote;
            } else if (*ptr == ' ' && !in_single_quote && !in_double_quote) {
                break; // Space ends the argument
            }
            *arg_ptr++ = *ptr++; // Copy character
        }

        if (in_single_quote || in_double_quote) {
            printf("Error: Mismatched quotes\n");
            free(arg);
            free(buffer);
            for (int i = 0; i < arg_count; i++) free(args[i]);
            free(args);
            return NULL;
        }

        *arg_ptr = '\0'; // Null-terminate argument
        if (*ptr) ptr++; // Skip space after argument

        // Expand argument array if needed
        if (arg_count >= arg_capacity) {
            int new_capacity = arg_capacity * 2;
            char **new_args = malloc(new_capacity * sizeof(char *));
            if (!new_args) {
                perror("malloc failed");
                free(arg);
                free(buffer);
                for (int i = 0; i < arg_count; i++) free(args[i]);
                free(args);
                return NULL;
            }
            for (int i = 0; i < arg_count; i++) {
                new_args[i] = args[i];
            }
            free(args);
            args = new_args;
            arg_capacity = new_capacity;
        }

        args[arg_count++] = arg; // Store argument
    }

    free(buffer);
    args[arg_count] = NULL; // Null-terminate the args array
    return args;
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
