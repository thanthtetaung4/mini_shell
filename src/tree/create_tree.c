#include "../../header/minishell.h"

char *copy_substring(const char *input, int start, int length)
{
	char *substring = malloc(length + 1);
	if (!substring)
		return NULL;
	ft_strlcpy(substring, input + start, length + 1);
	return substring;
}

// void handle_pipe_node(t_ast_node **head, char *input, t_substring *substring_data)
// {
// 	t_ast_node *temp;
// 	t_ast_node *temp_head;
// 	char *temp_input;

// 	if (!(*head))
// 	{
// 		*head = create_node(PIPE, NULL);
// 		temp_input = ft_strdup(input + substring_data->start + 1);
// 		temp = create_node(COMMAND, ft_split_quoted(temp_input, ' '));
// 		add_right_node(head, temp);
// 		free(temp_input);
// 	}
// 	else
// 	{
// 		temp_head = create_node(PIPE, NULL);
// 		temp_head->depth_level = (*head)->depth_level + 1;
// 		temp_input = copy_substring(input, substring_data->start + 1, substring_data->end - substring_data->start);
// 		temp = create_node(COMMAND, ft_split_quoted(temp_input, ' '));
// 		add_left_node(head, temp_head);
// 		*head = temp_head;
// 		add_right_node(head, temp);
// 		free(temp_input);
// 	}
// }

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
	}
	else
	{
		temp_head = create_node(type, NULL);
		temp_head->depth_level = (*head)->depth_level + 1;
		temp_input = copy_substring(input, substring_data->start + index, substring_data->end - substring_data->start);
		temp = create_node(COMMAND, ft_split_quoted(temp_input, ' '));
		add_left_node(head, temp_head);
		*head = temp_head;
		add_right_node(head, temp);
		free(temp_input);
	}
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
	if (input[substring_data->start] == '|')
	{
		handle_special_node(head, input, substring_data, PIPE);
		data->pipe_count++;
		substring_data->end = substring_data->start - 1;
	}
	else if (input[substring_data->start] == '>' && input[substring_data->start - 1] == '>')
	{
		// append
		handle_special_node(head, input, substring_data, APPEND);
		substring_data->end = substring_data->start - 2;
	}
	else if (input[substring_data->start] == '<' && input[substring_data->start - 1] == '<')
	{
		// heredoc
		handle_special_node(head, input, substring_data, HEREDOC);
		substring_data->end = substring_data->start - 2;
	}
	else if (input[substring_data->start] == '>' && input[substring_data->start - 1] != '>' && input[substring_data->start + 1] != '>')
	{
		// output
		handle_special_node(head, input, substring_data, OUTPUT);
		substring_data->end = substring_data->start - 1;
	}
	else if (input[substring_data->start] == '<' && input[substring_data->start - 1] != '<' && input[substring_data->start + 1] != '<')
	{
		// input
		handle_special_node(head, input, substring_data, INPUT);
		substring_data->end = substring_data->start - 1;
	}
}
t_ast_node *create_tree(char *input, t_minishell *data)
{
	t_substring *substring_data;
	t_ast_node *head;
	t_ast_node *lowest_node;

	if (!input || !data)
		return NULL;
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
