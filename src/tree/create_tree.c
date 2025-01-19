#include "../../header/minishell.h"

char *copy_substring(const char *input, int start, int length)
{
	char *substring = malloc(length + 1);
	if (!substring)
		return NULL;
	ft_strlcpy(substring, input + start, length + 1);
	return substring;
}

void handle_special_node(t_ast_node **head, char *input, t_substring *substring_data, int type)
{
	t_ast_node *temp;
	t_ast_node *temp_head;
	char *temp_input;
	int index;

	index = 1;
	if (type == HEREDOC || type == APPEND)
		index = 2;
	if (!(*head))
	{
		*head = create_node(type, NULL);
		temp_input = ft_strdup(input + substring_data->start + index);
		temp = create_node(COMMAND, ft_split_quoted(temp_input, ' '));
		add_right_node(head, temp);
		free(temp_input);
		return;
	}
	temp_head = create_node(type, NULL);
	temp_input = copy_substring(input, substring_data->start + index,
								substring_data->end - substring_data->start);
	temp = create_node(COMMAND, ft_split_quoted(temp_input, ' '));
	add_left_node(head, temp_head);
	*head = temp_head;
	add_right_node(head, temp);
	free(temp_input);
}

void handle_single_command(t_ast_node **head, char *input, int end, t_ast_node **lowest_node)
{
	t_ast_node *temp;
	char *temp_input;

	if (!(*(head)))
		*head = create_node(COMMAND, ft_split_quoted(input, ' '));
	else
	{
		temp_input = copy_substring(input, 0, end);
		temp = create_node(COMMAND, ft_split_quoted(temp_input, ' '));
		add_left_node(head, temp);
		*lowest_node = temp;
		free(temp_input);
	}
}
void handle_special_command(char *input, t_substring *substring_data, t_minishell *data, t_ast_node **head)
{
	int type;
	int index;

	type = 0;
	index = 1;
	if (input[substring_data->start] == '|')
		type = PIPE;
	else if (input[substring_data->start] == '>' && input[substring_data->start - 1] == '>')
		type = APPEND;
	else if (input[substring_data->start] == '<' && input[substring_data->start - 1] == '<')
		type = HEREDOC;
	else if (input[substring_data->start] == '>' && input[substring_data->start - 1] != '>' && input[substring_data->start + 1] != '>')
		type = OUTPUT;
	else if (input[substring_data->start] == '<' && input[substring_data->start - 1] != '<' && input[substring_data->start + 1] != '<')
		type = INPUT;
	if (type == HEREDOC || type == APPEND)
		index = 2;
	handle_special_node(head, input, substring_data, type);
	substring_data->end = substring_data->start - index;
	data->operator_count++;
}
t_ast_node *create_tree(char *input, t_minishell *data)
{
	t_substring *substring_data;
	t_ast_node *head;
	t_ast_node *lowest_node;

	substring_data = malloc(sizeof(t_substring));
	if (!substring_data)
		return NULL;
	substring_data->end = 0;
	substring_data->start = ft_strlen(input) - 1;
	head = NULL;
	lowest_node = NULL;
	while (substring_data->start >= 0)
	{
		if (input[substring_data->start] == '|' ||
			input[substring_data->start] == '>' ||
			input[substring_data->start] == '<')
			handle_special_command(input, substring_data, data, &head);
		else if (substring_data->start == 0)
			handle_single_command(&head, input, substring_data->end, &lowest_node);
		if (!lowest_node)
			lowest_node = head;
		substring_data->start--;
	}
	free(substring_data);
	return lowest_node;
}
