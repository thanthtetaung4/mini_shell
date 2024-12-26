#ifndef AST_H
#define AST_H

typedef enum
{
	PIPE,
	COMMAND,
} t_node_type;

typedef struct s_ast
{
	int type;
	struct s_ast *parent;
	struct s_ast *left;
	struct s_ast *right;
	char *command;
} t_ast_node;

t_ast_node *create_node(int type, char *command);
void add_right_node(t_ast_node **parent_node, t_ast_node *node);
void add_left_node(t_ast_node **parent_node, t_ast_node *node);

#endif
