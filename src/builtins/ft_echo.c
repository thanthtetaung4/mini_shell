/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 05:36:02 by taung             #+#    #+#             */
/*   Updated: 2025/02/19 17:00:02 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	print_star()
{
	struct dirent *entry;
    DIR *dir = opendir(".");
	int i;

	i = 0;
    if (dir == NULL) {
        perror("Unable to open directory");
        return EXIT_FAILURE;
    }

    while ((entry = readdir(dir)) != NULL) {
		if (entry->d_name[0] != '.')
		{
			if (i > 0)
				ft_putstr_fd(" ", 1);
        	ft_putstr_fd(entry->d_name, 1);
			i++;
		}

    }
    closedir(dir);
    return EXIT_SUCCESS;
}

int	ft_echo(t_minishell *data, t_ast_node *node)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if (node->command[i] && ft_strcmp(node->command[i], "-n") == 0)
	{
		n_flag = 1;
		i++;
	}
	while (node->command[i])
	{
		if (ft_strcmp(node->command[i], "*") == 0)
			print_star();
		else
			ft_putstr_fd(node->command[i], 1);
		if (node->command[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!n_flag)
		ft_putstr_fd("\n", 1);
	return (0);
}
