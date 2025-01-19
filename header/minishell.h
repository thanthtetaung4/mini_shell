#ifndef MINI_SHELL_H
#define MINI_SHELL_H
#include "../libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

typedef enum
{
	PIPE,
	HEREDOC,
	APPEND,
	INPUT,
	OUTPUT,
	COMMAND,
} t_node_type;

typedef struct s_substring
{
	int start;
	int end;
} t_substring;
typedef struct s_ast
{
	int type;
	struct s_ast *parent;
	struct s_ast *left;
	struct s_ast *right;
	char **command;
	int depth_level;
	int executed;
} t_ast_node;

typedef struct s_env
{
	char *key;
	char *value;
} t_env;

typedef struct s_minishell
{
	t_list *env;
	t_list *export;
	char **cmd;
	pid_t *pids;
	int **pipes;
	int pipe_count;
	int status;
} t_minishell;

// env functions
t_list *load_env(char **envp);
char **key_value_splitter(char *entry, char c);
char *ft_strncpy(char *dst, const char *src, size_t len);
int count_env(char **env);
void print_env(t_list **env);
void ft_add_env(t_list **env, t_list *new_node);
void ft_update_env(t_list **env, t_list *new_node);
char **get_env_strings(t_list *env);

// env struct functions
t_list *ft_envnew(char *key, char *value);

// export functions
void load_export_vars(t_minishell *data);
void print_export_vars(t_list **export);
int find_var(t_list **list, char *key);
void export_add_var(t_minishell *data, char *key, char *value);
void update_export_var(t_minishell *data, char *value, int index);
void add_var(t_minishell *data, t_list *new_node);
int is_valid_var(char *key);
void remove_quotes(char **str);
void replace_with_env_value(t_minishell *data, char **value);
void replace_with_env_value(t_minishell *data, char **value);

// exec functions
int ft_exec(char **cmd, t_minishell *data);

// builtins functions
void ft_env(t_env **env);
void ft_export(t_minishell *data, char **args);
void ft_unset(t_minishell *data, char **args);
void ft_exit(t_minishell *data, char **args);

// free functions
void free_all(t_minishell *data, char **cmd);
void free_cmd(char **cmd);
void env_free(void *env);

// utils functions
int ft_strcmp(const char *s1, const char *s2);
char **ft_split_quoted(char const *s, char c);

// tree functions
t_ast_node *create_node(int type, char **command);
void add_right_node(t_ast_node **parent_node, t_ast_node *node);
void add_left_node(t_ast_node **parent_node, t_ast_node *node);
t_ast_node *create_tree(char *input, t_minishell *data);
void visualize_tree(t_ast_node *lowest_node);
int tree_execution(t_ast_node *lowest_node, t_minishell *data);
#endif
