#include "../../header/minishell.h"

char *copy_substring(const char *input, int start, int length)
{
	char *substring = malloc(length + 1);
	if (!substring)
		return NULL;
	ft_strlcpy(substring, input + start, length + 1);
	return substring;
}

void handle_pipe_node(t_ast_node **head, char *input, t_substring *substring_data, t_minishell *data)
{
	t_ast_node *temp;
	t_ast_node *temp_head;
	char *temp_input;

	if (!(*head))
	{
		*head = create_node(PIPE, NULL, data);
		temp_input = ft_strdup(input + substring_data->start + 1);
		temp = create_node(COMMAND, ft_split_quoted(temp_input, ' '), data);
		add_right_node(head, temp);
		free(temp_input);
		substring_data->end = substring_data->start - 1;
		return;
	}
	temp_head = create_node(PIPE, NULL, data);
	temp_input = copy_substring(input, substring_data->start + 1,
								substring_data->end - substring_data->start);
	temp = create_node(COMMAND, ft_split_quoted(temp_input, ' '), data);
	add_left_node(head, temp_head);
	*head = temp_head;
	add_right_node(head, temp);
	free(temp_input);
	substring_data->end = substring_data->start - 1;
}

void handle_single_command(t_ast_node **head, char *input, int end, t_minishell *data)
{
	t_ast_node *temp;
	char *temp_input;

	if (!(*(head)))
		*head = create_node(COMMAND, ft_split_quoted(input, ' '), data);
	else
	{
		temp_input = copy_substring(input, 0, end);
		temp = create_node(COMMAND, ft_split_quoted(temp_input, ' '), data);
		add_left_node(head, temp);
		data->tree->lowest_node = temp;
		free(temp_input);
	}
}

t_ast_node *create_tree(char *input, t_minishell *data)
{
	t_substring *substring_data;
	t_ast_node *head;

	substring_data = malloc(sizeof(t_substring));
	if (!substring_data)
		return NULL;
	substring_data->end = 0;
	substring_data->start = ft_strlen(input) - 1;
	head = NULL;
	while (substring_data->start >= 0)
	{
		if (input[substring_data->start] == '|')
		{
			handle_pipe_node(&head, input, substring_data, data);
			data->forking->pipe_count += 1;
		}
		else if (substring_data->start == 0)
			handle_single_command(&head, input, substring_data->end, data);
		if (data->tree && !data->tree->lowest_node) 
			data->tree->lowest_node = head;
		substring_data->start--;
	}
	free(substring_data);
	return (data->tree->lowest_node);
}
