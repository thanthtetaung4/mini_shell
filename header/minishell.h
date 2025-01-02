# ifndef MINI_SHELL_H
# define MINI_SHELL_H
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>

typedef struct s_env
{
	char *key;
	char *value;
} t_env;

typedef struct s_minishell
{
	t_list	*env;
	t_list	*export;
} t_minishell;

//env loading functions
t_list	*load_env(char **envp);
char	**env_split(char *entry, char c);
char	*ft_strncpy(char *dst, const char *src, size_t len);
int		count_env(char **env);
void	print_env(t_list **env);
void	free_env(void *env);

//env struct functions
t_list	*ft_envnew(char *key, char *value);

//export functions
void	load_export_vars(t_minishell *data);
void	print_export_vars(t_list **export);

//exec functions
int	ft_exec(char *cmd, t_minishell *data);

//builtins functions
void ft_env(t_env **env);

//free functions
void	free_all(t_list **env);
# endif
