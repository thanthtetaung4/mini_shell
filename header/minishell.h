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

//env loading functions
t_list	*load_env(char **envp);
char	**env_split(char *entry, char c);
char	*ft_strncpy(char *dst, const char *src, size_t len);
int		count_env(char **env);
void	print_env(t_list **env);
void	free_env(void *env);

//env struct functions
t_list	*ft_envnew(char *key, char *value);

//exec functions
int	ft_exec(char *cmd, t_list **env);

//builtins functions
void ft_env(t_env **env);

//free functions
void	free_all(t_list **env);
# endif
