#ifndef PARSER_H
#define PARSER_H


/*::::::::::::    NOTE    ::::::::::::*/
#include "lexer.h"

/*:::::   FORWARD DECLARATION   ::::::*/
typedef struct s_ast_node    t_ast_node;


/*@@@@@@@@@@@ COMMAND NODE @@@@@@@@@@@*/
typedef struct			  s_command_node
{
	t_token_type			 token_type;
	char					**arguments;
	t_ast_node	 			 *left_node;
	t_ast_node				*right_node;
}
t_command_node;

/*@@@@@@@@@@@@ PIPE NODE @@@@@@@@@@@@@*/
typedef struct				s_pipe_node
{
	t_token_type			 token_type;
	t_ast_node	 			 *left_node;
	t_ast_node				*right_node;
}
t_pipe_node;

/*@@@@@@@@@@ REDIRECT NODE @@@@@@@@@@@*/
typedef struct			s_redirect_node
{
	t_token_type			 token_type;
	char						  *file;
	t_ast_node	 	 		*child_node;
}
t_redirect_node;

/*@@@@@@@@@@@@ UNION NODE @@@@@@@@@@@@*/
typedef union			 u_ast_node_type
{
	t_command_node		   command_node;
	t_pipe_node		  		  pipe_node;
	t_redirect_node		  redirect_node;
}
t_ast_node_type;

/*@@@@@@@@@@@@@ AST NODE @@@@@@@@@@@@@*/
typedef struct				  s_ast_node
{
	t_ast_node_type			  node_type;
	char				  		  *data;
}
t_ast_node;

/*:::::::::::::    NOTE    :::::::::::::::::
I need to create a  union so that  each node
type  can have a different struct. This will
help code be more organised
::::::::::::::::::::::::::::::::::::::::::*/

/*::::::::::::::::::::::::::        FUNCTIONS         ::::::::::::::::::::::::::::::*/

t_ast_node	*parser(t_token_node **lexer_list);
t_ast_node	*parse_pipe(t_token_node *lexer_list);
t_ast_node	*parse_command(t_token_node **lexer_list);
t_ast_node	*parse_redirect(t_token_node **lexer_list, t_ast_node *child);
void		ast_printer(t_ast_node **ast_tree, int depth, int is_last);

/*:::::::::::::::::::::::      HELPER FUNCTIONS        ::::::::::::::::::::::::::::::*/

int				is_redirect_token(t_token_type token);
int				count_words(t_token_node **lexer_list);
void			ast_printer(t_ast_node **ast_tree, int depth, int is_last);
char			**transfer_words(t_token_node **lexer_list);
static void		print_indent(int depth, int is_last);
t_token_node	*move_forward(t_token_node **lexer_list);

#endif // PARSER_H
