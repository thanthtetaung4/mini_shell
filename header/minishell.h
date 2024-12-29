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
	struct s_env *next;
} t_env;

void	map(char *entry, char **key, char **value);
int		count_env(char **env);
t_env	*load_env(char **envp);
void	print_env(t_env **env);
void	free_env(t_env **env);
void	ft_envclear(t_env **lst, void (*del)(void*));
char	**env_split(char *entry, char c);
char	*ft_strncpy(char *dst, const char *src, size_t len);

//env struct functions
t_env	*ft_envnew(char *key, char *value);
t_env	*ft_envlast(t_env *lst);
void	ft_envadd_back(t_env **alst, t_env *new);
void	ft_envdelone(t_env *lst, void (*del)(void*));
void	ft_envclear(t_env **lst, void (*del)(void*));

//exec functions
int	ft_exec(char *cmd, t_env **env);

//builtins functions
void ft_env(t_env **env);

//free functions
void	free_all(t_env **env);
# endif
