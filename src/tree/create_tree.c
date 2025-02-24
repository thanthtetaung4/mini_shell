#include "../../header/minishell.h"

void handle_pipe_node(t_ast_node **head, char **cmd ,t_minishell *data, int count)
{
    t_ast_node *temp;
    t_ast_node *temp_head;
    char *temp_input;

    if (!(*head))
    {
        *head = create_node(PIPE, NULL, data, 1);
        temp = create_node(COMMAND, cmd, data, count);
        add_right_node(head, temp);
        return;
    }
	temp_head = create_node(PIPE, NULL, data, 1);
	temp = create_node(COMMAND, cmd, data, count);
    add_left_node(head, temp_head);
    *head = temp_head;
    add_right_node(head, temp);
}

void handle_single_command(t_ast_node **head, char **cmd, t_minishell *data, int count)
{
    t_ast_node *temp;
    // char *temp_input;
    if (!(*(head)))
	{
        *head = create_node(COMMAND, cmd, data, count);
		data->tree->lowest_node = *head;
		// printf("%s\n", (*head)->command[0]);
	}
	else
    {
        temp = create_node(COMMAND, cmd, data, count);
        add_left_node(head, temp);
        data->tree->lowest_node = temp;
		temp = NULL;
    }
}
void reset_args(char **args, int counter)
{
	int i;

	i = 0;
	while (i < counter)
	{
		args[i] = NULL;
		i++;
	}
}
t_ast_node *create_tree(t_minishell *data)
{
    t_ast_node *head;
    int i;
    int j;
	int counter;
	char *cmd[256];

	i = data->args_count - 1;
	counter = 0;
	head = NULL;
	while (i >= 0)
	{
		j = 0;
		// if ((data->args[i][0] == '>' || data->args[i][0] == '<') && data->args[i + 1])
		// 	counter--;
		// else
		counter++;
		if (ft_strcmp(data->args[i], "|") == 0)
		{
			while (j < counter - 1)
			{
				cmd[j] = data->args[i + j + 1];
				j++;
			}
			cmd[j] = NULL;
			handle_pipe_node(&head, cmd, data, counter - 1);
			counter = 0;
			data->forking->pipe_count += 1;
		}
		else if (i == 0)
		{
			while (j <= counter)
			{
				cmd[j] = data->args[i + j];
				j++;
			}
			cmd[j] = NULL;
			handle_single_command(&head, cmd, data, counter);
			counter = 0;
		}
        // if (data->tree && !data->tree->lowest_node)
		// {
        //     data->tree->lowest_node = head;
		// 	// printf("lowest node - %s\n", data->tree->lowest_node->command[0]);
		// }
        i--;
    }
	// free(head);
    return (data->tree->lowest_node);
}
