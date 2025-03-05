#include "../../header/minishell.h"

int	check_valid_args(char *arg)
{
	int	i;
	int	sign;

	if (!arg)
		return (0);
	i = 0;
	sign = 0;
	if (arg[i] == '-' || arg[i] == '+')
	{
		sign = 1;
		i++;
	}
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	if (sign && i == 1)
		return (0);
	return (1);
}

void	ft_exit(t_minishell *data, t_ast_node *node)
{
	int	exit_status;
	int	cmd_count;

	cmd_count = ft_count_tds(node->command);
	if (!node->command[1])
	{
		free_all(data, 1);
		ft_putstr_fd("exit\n", 0);
		exit(0);
	}
	else if (cmd_count == 2)
	{
		if (!check_valid_args(node->command[1]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(node->command[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			free_all(data, 1);
			exit(2);
		}
		else
		{
			exit_status = ft_atoi(node->command[1]);
			free_all(data, 1);
			exit(exit_status % 256);
		}
	}
	else if (cmd_count > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return;
	}
}