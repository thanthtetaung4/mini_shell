#include "../../header/minishell.h"

int	count_pnr(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while(input[i])
	{
		if (input[i] == '|' && input[i] == '<' && input[i] == '>')
			count++;
		i++;
	}
	return (count);
}

char	*ft_insert_spaces(char *input)
{
	int	i;
	int	j;
	int	count;
	char	*new_input;

	i = 0;
	j = 0;
	count = count_pnr(input);
	new_input = malloc(ft_strlen(input) + (count * 2) + 1);
	if (!new_input)
		return NULL;
	while (input[i])
	{
		if (input[i] == '|' || input[i] == '>' || input[i] == '<')
		{
			if (input[i + 1] == '>' || input[i + 1] == '<')
			{
				new_input[j] = ' ';
				new_input[j + 1] = input[i];
				new_input[j + 2] = input[i + 1];
				new_input[j + 3] = ' ';
				i += 2;
				j += 4;
			}
			else
			{
				new_input[j] = ' ';
				new_input[j + 1] = input[i];
				new_input[j + 2] = ' ';
				i++;
				j += 3;
			}
		}
		else
		{
			new_input[j] = input[i];
			i++;
			j++;
		}
	}
	new_input[j] = '\0';
	// printf("new_input: %s, count: %ld\n", new_input, ft_strlen(new_input));
	free(input);
	return (new_input);
}
