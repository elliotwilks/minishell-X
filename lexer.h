#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*@@@@@@@@@@@@@@  ENUM  @@@@@@@@@@@@@@*/
typedef enum e_token_type
{
  	TOKEN_PIPE,
    TOKEN_WORD,
    TOKEN_DOLLAR,
    TOKEN_INPUT,
    TOKEN_OUTPUT,
    TOKEN_HEREDOC,
    TOKEN_APPEND_OUTPUT,
    TOKEN_EOF,
}
t_token_type;

/*@@@@@@@@@@@  TOKEN NODE  @@@@@@@@@@@*/
typedef struct s_token_list
{
	char                           *input;
	t_token_type                    token;
	struct s_token_list             *next;
}
t_token_node;

/*XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX   FUNCTIONS   XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX*/
char            *ft_substr(char const *s, unsigned int start, size_t len);
size_t          ft_strlcpy(char *dst, const char *src, size_t dstsize);
void            print_lexer_list(t_token_node *lexer_list);
void            free_full_list(t_token_node *head);
char            *ft_strdup(const char *s1);
size_t          ft_strlen(const char *str);
int             ft_isalpha(int c);
int             is_token(char c);
t_token_node    *lexer(char *input);
t_token_node    *create_node(t_token_type token, char *input);
t_token_node    *append_node(t_token_node **head, t_token_type token, char *input);

#endif  //LEXER_H
