/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 06:42:51 by codespace         #+#    #+#             */
/*   Updated: 2025/01/22 06:08:37 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

int	count_export(t_list *env)
{
	int		n;
	t_list	*current;

	n = 0;
	current = env;
	while (current)
	{
		if (((t_env *)current->content)->key[0] == '_')
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
				((t_env *)current_export->next->content)->key,
				ft_strlen(((t_env *)new_node->content)->key)) < 0)
		{
			new_node->next = current_export->next;
			current_export->next = new_node;
			return ;
		}
		current_export = current_export->next;
	}
	current_export->next = new_node;
}

void	add_var(t_minishell *data, t_list *new_node)
{
	t_list	*current_export;
	t_list	*prev_export;

	if (!data->export || ft_strcmp(((t_env *)data->export->content)->key,
			((t_env *)new_node->content)->key) > 0)
	{
		insert_at_beginning(data, new_node);
		return ;
	}
	current_export = data->export;
	prev_export = NULL;
	while (current_export && ft_strcmp(((t_env *)current_export->content)->key,
			((t_env *)new_node->content)->key) < 0)
	{
		prev_export = current_export;
		current_export = current_export->next;
	}
	if (prev_export)
		prev_export->next = new_node;
	new_node->next = current_export;
}

void	load_export_vars(t_minishell *data)
{
	t_list	*current;

	current = data->env;
	while (current)
	{
		if (((t_env *)current->content)->key[0] != '_')
			add_var(data, ft_envnew(((t_env *)current->content)->key,
					((t_env *)current->content)->value));
		current = current->next;
	}
	return ;
}

void	print_export_vars(t_list **export)
{
	t_list	*current;

	current = *export;
	while (current)
	{
		printf("%s=\"%s\"\n", ((t_env *)current->content)->key,
			((t_env *)current->content)->value);
		current = current->next;
	}
	return ;
}

int	find_var(t_list **list, char *key)
{
	t_list	*current;
	int		i;

	i = 0;
	current = *list;
	while (current && current->content)
	{
		if (ft_strcmp(key, ((t_env *)current->content)->key) == 0)
		{
			return (i);
		}
		current = current->next;
		i++;
	}
	return (-1);
}

int	is_valid_var(char *key)
{
	int	i;

	i = 0;
	if (ft_isalpha(key[i]) || key[i] == '_' || key[i] == 34 || key[i] == 39)
	{
		i++;
		while (key[i])
		{
			if (ft_isalnum(key[i]) || key[i] == '_' || key[i] == 34
				|| key[i] == 39)
				i++;
			else
				return (0);
		}
		return (1);
	}
	return (0);
}
