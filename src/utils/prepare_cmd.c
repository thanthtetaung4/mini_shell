#include "../../header/minishell.h"

int	count_pnr(char *input)
{
	int	i = 0;
	int	count = 0;

	while (input[i])
	{
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
		{
			count++;
			if ((input[i] == '<' || input[i] == '>') && input[i + 1] == input[i])
				i++;
		}
		i++;
	}
	return (count);
}


char	*ft_insert_spaces(char *input)
{
	int		i;
	int j;
	int count;
	char	*new_input;

	count = count_pnr(input);
	i = 0;
	j = 0;
	new_input = malloc(ft_strlen(input) + (count * 2) + 1);
	if (!new_input)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '|' || input[i] == '>' || input[i] == '<')
		{
			new_input[j++] = ' ';
			new_input[j++] = input[i];
			if ((input[i] == '>' || input[i] == '<') && input[i + 1] == input[i])
				new_input[j++] = input[++i];
			new_input[j++] = ' ';
			i++;
		}
		else
			new_input[j++] = input[i++];
	}
	new_input[j] = '\0';
	free(input);
	return (new_input);
}
