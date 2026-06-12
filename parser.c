#include "parser.h"
#include "lexer.h"

/*:::::::::::::::::::      FORWARD DECLARATION        :::::::::::::::::::::::::*/

t_ast_node			 	  			 *parse_command(t_token_node **lexer_list);
t_token_node						  *move_forward(t_token_node **lexer_list);

/*:::::::::::::::::::::::      START HERE        ::::::::::::::::::::::::::::::*/

t_ast_node	*parser(t_token_node **lexer_list)
{
	t_ast_node	*ast_tree;

	if (lexer_list == NULL)
		return (NULL);

	ast_tree = parse_pipe(*lexer_list);
	if (ast_tree == NULL)
		return (NULL);

	return (ast_tree);
}

t_ast_node	*parse_pipe(t_token_node *lexer_list)
{
	t_ast_node		*pipe_node;
	t_ast_node		*left_node;

	left_node = parse_command(&lexer_list);

	if (lexer_list->token == TOKEN_PIPE)
	{
		move_forward(&lexer_list);
		pipe_node = malloc(sizeof(t_ast_node));
		pipe_node->node_type.pipe_node.token_type = TOKEN_PIPE;
		pipe_node->node_type.pipe_node.left_node = left_node;
		pipe_node->node_type.pipe_node.right_node = parse_pipe(lexer_list);
	}
	else
		return (left_node);
	return (pipe_node);
}

t_ast_node	*parse_command(t_token_node **lexer_list)
{
	char					  **arguments;
	t_ast_node	 			*command_node;

	command_node = NULL;
	if ((*lexer_list)->token == TOKEN_WORD)
	{
		command_node = malloc(sizeof(t_ast_node));
		arguments = transfer_words(lexer_list);

		command_node->node_type.command_node.token_type = TOKEN_WORD;
		command_node->node_type.command_node.arguments = arguments;

		while ((*lexer_list)->token == TOKEN_WORD)
			move_forward(lexer_list);
	}
	if ((*lexer_list)->token == TOKEN_EOF)
		return (command_node);

	return (parse_redirect(lexer_list, command_node));
}

t_ast_node	*parse_redirect(t_token_node **lexer_list, t_ast_node *child)
{
	char			*file;
	t_token_type	token;
	t_ast_node		*redirect_node;

	if (lexer_list == NULL || (*lexer_list)->token == TOKEN_EOF)
		return (child);

	if (is_redirect_token((*lexer_list)->token) == 1)
	{
		redirect_node = malloc(sizeof(t_ast_node));

		token = (*lexer_list)->token;
		file = ft_strdup((*lexer_list)->next->input);

		redirect_node->node_type.redirect_node.token_type = token;
		redirect_node->node_type.redirect_node.child_node = child;
		redirect_node->node_type.redirect_node.file       = file;

		move_forward(lexer_list); // Move past the redirect
		move_forward(lexer_list); // Move past the file name

		return (parse_redirect(lexer_list, redirect_node));
	}
	return (child);
}

