#include "../../header/ast.h"
#include "../../header/minishell.h"

char *copy_substring(const char *input, int start, int length)
{
	char *substring = malloc(length + 1);
	if (!substring)
		return NULL;
	ft_strlcpy(substring, input + start, length + 1);
	return substring;
}

void handle_pipe_node(t_ast_node **head, char *input, int len, int end)
{
	t_ast_node *temp;
	t_ast_node *temp_head;
	char *temp_input;

	if (!(*head))
	{
		*head = create_node(PIPE, NULL);
		temp = create_node(COMMAND, ft_strdup(input + len + 1));
		add_right_node(head, temp);
	}
	else
	{
		temp_head = create_node(PIPE, NULL);
		temp_head->depth_level = (*head)->depth_level + 1;

		temp_input = copy_substring(input, len + 1, end - len);
		temp = create_node(COMMAND, temp_input);

		add_left_node(head, temp_head);
		*head = temp_head;
		add_right_node(head, temp);
	}
}

void handle_single_command(t_ast_node **head, char *input, int end, t_ast_node **lowest_node)
{
	t_ast_node *temp;
	char *temp_input;

	if (!(*(head)))
		*head = create_node(COMMAND, ft_strdup(input));
	else
	{
		temp_input = copy_substring(input, 0, end);
		temp = create_node(COMMAND, temp_input);
		add_left_node(head, temp);
		*lowest_node = temp;
	}
}

t_ast_node *create_tree(char *input)
{
	int len;
	int end;
	t_ast_node *head;
	t_ast_node *lowest_node;

	len = ft_strlen(input) - 1;
	end = 0;
	head = NULL;
	lowest_node = NULL;
	while (len >= 0)
	{
		if (input[len] == '|')
		{
			handle_pipe_node(&head, input, len, end);
			end = len - 1;
		}
		else if (len == 0)
			handle_single_command(&head, input, end, &lowest_node);
		if (!lowest_node)
			lowest_node = head;
		len--;
	}
	return lowest_node;
}
