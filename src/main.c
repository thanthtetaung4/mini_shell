/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taung <taung@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:23:27 by taung             #+#    #+#             */
/*   Updated: 2024/12/16 18:07:03 by taung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#include <readline/readline.h>

int main()
{
	printf("hello world\n");
	char *line = readline("Enter a line >>");
	printf("%s\n", line);
}
