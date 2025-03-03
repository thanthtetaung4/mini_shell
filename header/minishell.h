/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshein <lshein@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:33:51 by taung             #+#    #+#             */
/*   Updated: 2025/03/03 11:48:26 by lshein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

typedef enum s_node_type
{
	PIPE,
	HEREDOC,
	APPEND,
	INPUT,
	OUTPUT,
	COMMAND,
}					t_node_type;

typedef struct s_substring
{
	int				start;
	int				end;
}					t_substring;

typedef struct s_redirections
{
	int				*types;
	char			**files;
	int				*file_fds;
	int				redirection_count;
	int				heredoc_count;
	int				heredoc_fd[2];
}					t_redirections;

typedef struct s_ast
{
	int				type;
	struct s_ast	*parent;
	struct s_ast	*left;
	struct s_ast	*right;
	t_redirections	*redirection;
	char			**command;
	int				executed;
}					t_ast_node;

typedef struct s_tree
{
	t_ast_node		*lowest_node;
}					t_tree;

typedef struct s_env
{
	char			*key;
	char			*value;
}					t_env;

typedef struct s_forking
{
	pid_t			*pids;
	int				**fds;
	int				*redirection_fds;
	int				input_fd;
	int				output_fd;
	int				completed_piping;
	int				pipe_count;
	int				heredoc_count;
	int				redirection_count;
	int				i_pid;
	int				i_rfd;
	int				i_fd;
}					t_forking;

typedef struct s_minishell
{
	t_list			*env;
	char			*input;
	t_list			*export;
	char			**args;
	int				status;
	int				args_count;
	t_tree			*tree;
	t_forking		*forking;
	int				heredoc_backup;
	int				stdin_backup;
	int				empty_prev_node;
}					t_minishell;

// Structure to hold parsing state
typedef struct s_parse_state
{
	char			**args;
	int				arg_count;
	int				arg_capacity;
	char			*buffer;
	bool			in_single_quote;
	bool			in_double_quote;
	bool			error;
}					t_parse_state;

typedef struct s_f_cmd_path
{
	char			*path_env;
	char			*path_dup;
	char			**dir;
	char			*full_path;
	int				i;
}					t_f_cmd_path;

// env functions
t_list				*load_env(char **envp);
char				**key_value_splitter(char *entry, char c);
char				*ft_strncpy(char *dst, const char *src, size_t len);
int					count_env(char **env);
void				print_env(t_list **env);
void				ft_add_env(t_list **env, t_list *new_node);
void				ft_update_env(t_list **env, t_list *new_node);
char				**get_env_strings(t_list *env);
char				*ft_get_env(t_minishell *data, char *key);
// env struct functions
t_list				*ft_envnew(char *key, char *value);

// export functions
void				load_export_vars(t_minishell *data);
void				print_export_vars(t_list **export);
int					find_var(t_list **list, char *key);
void				export_add_var(t_minishell *data, char *key, char *value);
void				update_export_var(t_minishell *data, char *value,
						int index);
void				add_var(t_minishell *data, t_list *new_node);
int					is_valid_var(char *key);
void				remove_cmd_quote(t_minishell *data);
void				replace_with_env_value(t_minishell *data, char **value);
void				replace_with_env_value(t_minishell *data, char **value);
char				*get_env_value(t_list *env, char *key);

// exec functions
int					ft_exec(t_minishell *data, t_ast_node *node);

// builtins functions
int					ft_env(t_env **env);
int					ft_export(t_minishell *data, t_ast_node *node);
int					ft_unset(t_minishell *data);
void				ft_exit(t_minishell *data);
int					ft_pwd(void);
int					ft_cd(t_minishell *data);
int					ft_echo(t_minishell *data, t_ast_node *node);
// cd utils
int					handle_cd_error(char *pwd, const char *message);
void				update_prev_dir(t_minishell *data, char *prev_dir);
void				update_env_pwd(t_minishell *data);

// free functions
void				free_all(t_minishell *data, int free_execution_data);
void				free_cmd(char ***cmd);
void				env_free(void *env);
void				free_tree(t_ast_node *node);
void				free_2d_string(char **str);

// utils functions
int					ft_strcmp(const char *s1, const char *s2);
char				**ft_split_quoted(char const *s, char c);
int					ft_count_tds(char **str);
char				*ft_strrchr(const char *s, int c);
int					ft_strnchr(char *str, int n, int c);
void				ft_interpret(t_minishell *data);
char				*ft_insert_spaces(char *input);
char				**split_args(const char *input);
void				remove_empty_args(t_minishell *data);
char				*find_command_path(char *cmd, t_minishell *data);
void				init_helper(t_parse_state *state);
t_parse_state		*init_parse_state(const char *input);
void				cleanup_parse_state(t_parse_state *state);
bool				resize_args_array(t_parse_state *state);
char				*skip_spaces(char *ptr);
void				handle_quote(char c, t_parse_state *state);
char				*get_value_before_dollar(char *cmd, char *found_dollar);
char				*get_value_after_variable(char *cmd, char *pos);
char				*get_value(t_minishell *data, t_list *env,
						char *found_dollar, char **pos);
void				wrod_count_helper(char s, int *in_quotes, char *quote_char);
size_t				ft_word_count(char *s, char c);

// signal functions
void				handle_sigint(int sig);
void				handle_sigquit(int sig);
void				handle_sigquit_child(int sig);
void				handle_sigint_child(int sig);
void				setup_child_signals(void);
void				handle_heredoc_sigint(int sig);
void				set_signals_heredoc(void);

// test utils
void				ft_print_args(char **args);

// redirection functions
char				**get_heredoc_delimiters(t_ast_node *node);
int					setup_heredoc_pipe(t_ast_node *node);
int					process_delimiter_match(char *line, char **delimiters,
						int *current_delimiter, int heredoc_count);
void				write_to_heredoc(char *line, t_ast_node *node,
						int current_delimiter);
int					read_heredoc_input(t_ast_node *node, char **delimiters);
int					heredoc(t_minishell *data, t_ast_node *node,
						int inside_pipe);
// ast functions
int					check_redirection(char *arg);
void				redirection_counter(t_minishell *data, t_ast_node *node,
						char **command);
void				allocate_redirection_memory(t_ast_node *node);
void				fill_redirection_data(t_minishell *data, t_ast_node *node,
						char **command);
void				init_redirection_data(t_minishell *data, t_ast_node *node,
						char **command);
t_ast_node			*allocate_node(int type);
void				fill_command_data(t_ast_node *node, char **command,
						int count);
t_ast_node			*create_node(int type, char **command, t_minishell *data,
						int count);
void				add_right_node(t_ast_node **parent_node, t_ast_node *node);
void				add_left_node(t_ast_node **parent_node, t_ast_node *node);

// redirection_handling
int					handle_output_redirection(t_ast_node *node,
						t_minishell *data, int i);
int					handle_input_redirection(t_ast_node *node,
						t_minishell *data, int i);
int					handle_heredoc_redirection(t_ast_node *node);
int					handle_existing_file_redirection(t_ast_node *node,
						t_minishell *data, int i);
int					handle_new_file_redirection(t_ast_node *node,
						t_minishell *data, int i);
// inits
void				init_forking_data(t_minishell *data);
int					init_pids(t_minishell *data);
void				init_fds(t_minishell *data);
int					init_data(t_minishell *data, char **envp);
// tree functions
t_ast_node			*create_tree(t_minishell *data);
int					tree_execution(t_ast_node *lowest_node, t_minishell *data);
int					ft_count_tds(char **str);
char				*ft_strrchr(const char *s, int c);
void				init_forking_data(t_minishell *data);
void				reset_forking_data(t_minishell *data);
int					execute_command(t_minishell *data, t_ast_node *node);
void				free_heredoc(char *line, char **delimiters);
// execution_utils
int					execute_external_cmd(t_minishell *data, t_ast_node *node);
int					execute_single_command(t_minishell *data, t_ast_node *node);
void				execute_pipe_child(t_minishell *data, t_ast_node *node);
int					execute_pipe_command(t_minishell *data, t_ast_node *node);
int					setup_execution_context(t_minishell *data);
// tree utils
int					check_cmd(char *cmd);
void				save_std_fds(t_ast_node *node, int *stdout_fd,
						int *stdin_fd);
void				restore_std_fds(int stdout_fd, int stdin_fd);
// execute_redirection
int					handle_heredoc_if_needed(t_ast_node *node, int i);
int					process_file_redirection(t_ast_node *node,
						t_minishell *data, int i);
int					execute_redirection(t_ast_node *node, t_minishell *data);
int					execute_builtin_with_redirections(t_minishell *data,
						t_ast_node *node, int stdout_fd, int stdin_fd);
// pipe_utils
void				setup_stdin_for_pipe(t_minishell *data, t_ast_node *node);
void				setup_stdout_for_pipe(t_minishell *data);
void				handle_pipe_parent(t_minishell *data, t_ast_node *node,
						int pid);
void				handle_pipe_execution(t_minishell *data, t_ast_node *node);
int					handle_pipe_heredoc(t_minishell *data, t_ast_node *node);

// heredoc_utils
char				**get_heredoc_delimiters(t_ast_node *node);
int					setup_heredoc_pipe(t_ast_node *node);
int					process_delimiter_match(char *line, char **delimiters,
						int *current_delimiter, int heredoc_count);
void				write_to_heredoc(char *line, t_ast_node *node,
						int current_delimiter);
int					read_heredoc_input(t_ast_node *node, char **delimiters);

// execution_utils_2
void				setup_child_process(t_minishell *data, t_ast_node *node);
int					handle_child_exit_status(int exit_status);
void				handle_empty_command_child(t_minishell *data);
void				update_empty_prev_node(t_minishell *data, t_ast_node *node);
int					handle_command_heredoc(t_minishell *data, t_ast_node *node);

// execution_utils_3
int					process_heredocs(t_ast_node *lowest_node,
						t_minishell *data);
void				handle_command_execution(t_minishell *data,
						t_ast_node *node);
void				execute_commands(t_ast_node *lowest_node,
						t_minishell *data);
void				wait_for_children(t_minishell *data);
void				handle_signal_status(t_minishell *data);
// tree_creation_utils
void				handle_pipe_node(t_ast_node **head, char **cmd,
						t_minishell *data, int count);
void				handle_single_command(t_ast_node **head, char **cmd,
						t_minishell *data, int count);
void				reset_args(char **args, int counter);
void				process_pipe_node(t_ast_node **head, t_minishell *data,
						int *counter, int i);
void				process_single_command(t_ast_node **head, t_minishell *data,
						int *counter, int i);
// fd
void				close_heredoc_fds_c(t_minishell *data);
void				close_heredoc_fds_p(t_minishell *data);
void				setup_pipe_fds(t_minishell *data);
void				close_all_pipe_fds(t_minishell *data);
// fd_utils
void				close_backup_fds(t_minishell *data);
void				close_pipe_fds(t_minishell *data);
#endif
