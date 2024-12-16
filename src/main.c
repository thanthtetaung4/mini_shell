/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tha <tha@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:23:27 by taung             #+#    #+#             */
/*   Updated: 2024/12/16 21:44:20 by tha              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int main()
{
	printf("hello world\n");
	char *line = readline("Enter a line >>");
	printf("%s\n", line);
}
