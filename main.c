#include "executor.h"
#include "lexer.h"
#include "parser.h"

int main(void)
{
    t_token_node    *lexer_list;
    t_ast_node      *ast_tree;

    lexer_list = lexer("echo hello | grep hello > file");

    ast_tree = parser(&lexer_list);

    ast_printer(&ast_tree, 0, 1);

    return (0);
}
