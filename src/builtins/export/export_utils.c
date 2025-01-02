/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 06:42:51 by codespace         #+#    #+#             */
/*   Updated: 2025/01/02 14:41:48 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

int	count_export(t_list *env)
{
	int n;
	t_list *current;

	n = 0;
	current = env;
	while (current)
	{
		if (((t_env*)current->content)->key[0] == '_')
			n++;
		current = current->next;
	}
	return (n);
}

void	insert_at_beginning(t_minishell *data, t_list *new_node)
{
	new_node->next = data->export;
	data->export = new_node;
}

void	insert_in_middle_or_end(t_list *current_export, t_list *new_node)
{
	while (current_export->next)
	{
		if (ft_strncmp(((t_env *)new_node->content)->key,
						((t_env *)current_export->next->content)->key, ft_strlen(((t_env *)new_node->content)->key)) < 0)
		{
			new_node->next = current_export->next;
			current_export->next = new_node;
			return;
		}
		current_export = current_export->next;
	}
	current_export->next = new_node;
}

void	add_var(t_minishell *data, t_list *new_node)
{
	t_list	*current_export;

	if (!data->export)
	{
		data->export = new_node;
		return;
	}
	if (ft_strncmp(((t_env *)new_node->content)->key,
					((t_env *)data->export->content)->key, ft_strlen(((t_env *)new_node->content)->key)) < 0)
	{
		insert_at_beginning(data, new_node);
		return;
	}
	current_export = data->export;
	insert_in_middle_or_end(current_export, new_node);
}

void	load_export_vars(t_minishell *data)
{
	t_list	*current;

	current = data->env;
	printf("Loading export vars\n");
	while (current)
	{
		if (((t_env*)current->content)->key[0] != '_')
			add_var(data, ft_envnew(((t_env*)current->content)->key, ((t_env*)current->content)->value));
		current = current->next;
	}
	return;
}

void	print_export_vars(t_list **export)
{
	t_list	*current;

	current = *export;
	while(current)
	{
		printf("%s=\"%s\"\n", ((t_env*)current->content)->key, ((t_env*)current->content)->value);
		current = current->next;
	}
	return;
}
