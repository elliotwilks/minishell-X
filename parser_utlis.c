#include "parser.h"

/*:::::::::::::::::::::::      HELPER FUNCTIONS        ::::::::::::::::::::::::::::::*/

int		is_redirect_token(t_token_type token)
{
	if (token == TOKEN_INPUT || token == TOKEN_OUTPUT || token == TOKEN_HEREDOC || token == TOKEN_APPEND_OUTPUT)
		return (1);
	return (0);
}

t_token_node	*move_forward(t_token_node **lexer_list)
{
	t_token_node	*current;

	if (lexer_list == NULL)
		return (NULL);

	current = *lexer_list;
	*lexer_list = (*lexer_list)->next;
	return (current);
}

int		count_words(t_token_node **lexer_list)
{
	int				count;
	t_token_node	*current;

	current = *lexer_list;
	count = 0;
	while (current->token == TOKEN_WORD)
	{
		current = current->next;
		count++;
	}
	return (count);
}

char	**transfer_words(t_token_node **lexer_list)
{
	int				i;
	int				word_count;
	t_token_node	*current;
	t_token_node	*start;
	char			**arguments;

	word_count = 0;
	start = *lexer_list;
	current = *lexer_list;

	while (start->token == TOKEN_WORD)
	{
		word_count++;
		start = start->next;
	}

	arguments = malloc(sizeof(char *) * (word_count + 1));
	if (arguments == NULL)
		return (NULL);

	i = 0;
	while (current->token == TOKEN_WORD)
	{
		arguments[i] = ft_strdup(current->input);
		current = current->next;
		i++;
	}
	arguments[i] = NULL;
	return (arguments);
}

static void	print_indent(int depth, int is_last)
{
	int	i;

	i = 0;
	while (i < depth - 1)
	{
		printf("│   ");
		i++;
	}
	if (depth > 0)
		printf(is_last ? "└── " : "├── ");
}

void	ast_printer(t_ast_node **ast_tree, int depth, int is_last)
{
	t_ast_node		*ast;
	t_token_type	type;
	int				i;

	if (!ast_tree || !*ast_tree)
		return ;
	ast = *ast_tree;
	print_indent(depth, is_last);

	type = ast->node_type.pipe_node.token_type;

	if (type == TOKEN_PIPE)
	{
		printf("[PIPE]\n");
		ast_printer(&ast->node_type.pipe_node.left_node,  depth + 1, 0);
		ast_printer(&ast->node_type.pipe_node.right_node, depth + 1, 1);
	}
	else if (type == TOKEN_INPUT || type == TOKEN_OUTPUT
		|| type == TOKEN_HEREDOC || type == TOKEN_APPEND_OUTPUT)
	{
		printf("[REDIRECT] %s\n", ast->node_type.redirect_node.file);
		ast_printer(&ast->node_type.redirect_node.child_node,  depth + 1, 0);
	}
	else
	{
		printf("[CMD]");
		i = 0;
		while (ast->node_type.command_node.arguments[i])
		{
			printf(" %s", ast->node_type.command_node.arguments[i]);
			i++;
		}
		printf("\n");
	}
}

/*
Learning:

"Tail Call" chaining is when a function's final action
is returning the immediate result of calling another
function.
*/
