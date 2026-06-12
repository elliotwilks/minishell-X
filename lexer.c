#include "lexer.h"

int		is_token(char c)
{
	if (c == '$' || c == '|' || c == '>'
			|| c == '>' || c == '<' || c == 39 || c == '"')
		return (1);
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	srclen;

	srclen = ft_strlen(src);
	if (dstsize == 0)
		return (srclen);
	i = 0;
	while (i < (dstsize - 1) && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (srclen);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	len;

	len = ft_strlen(s1) + 1;
	s2 = malloc(len * sizeof(char));
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, s1, len);
	return (s2);
}

void    print_lexer_list(t_token_node   *lexer_list)
{
    while (lexer_list != NULL)
    {
        printf("\nNODE\n");
        printf("Token Type: %d\n", lexer_list->token);
        printf("Input Value : %s\n", lexer_list->input);
        lexer_list = lexer_list->next;
    }
}

void    free_full_list(t_token_node     *head)
{
    t_token_node    *temp;

    temp = head;
    while (temp != NULL)
    {
        temp = head->next;
        free(head);
        head = temp;
    }
}

int     ft_isalpha(int c)
{
    if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
    {
        return (c);
    }
    return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	char	*src;
	size_t	reslen;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < (size_t)start)
		return (ft_strdup(""));
	src = (char *)s + start;
	if (ft_strlen(src) < len)
		reslen = ft_strlen(src) + 1;
	else
		reslen = len + 1;
	res = malloc(reslen * sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res, src, reslen);
	return (res);
}

t_token_node    *create_node(t_token_type token, char *input)
{
    t_token_node    *node;

    node = malloc(sizeof(t_token_node));
    if (node == NULL)
        return (NULL);

    node->token = token;
    node->input = input;
    node->next = NULL;
    return (node);
}

t_token_node    *append_node(t_token_node **head, t_token_type token, char *input)
{
    t_token_node    *last_node;
    t_token_node   *new_node;

    last_node = *head;

    new_node = create_node(token, input);

    if (*head == NULL)
    {
        *head = new_node;
        return (new_node);
    }
    while (last_node->next != NULL)
    {
        last_node = last_node->next;
    }
    last_node->next = new_node;
    return (new_node);
}

t_token_node    *lexer(char *input)
{
    int             i;
    int             start;
    t_token_node    *head;

    head = NULL;

    i = 0;
    while (input[i])
    {
        if (input[i] == '|')
        {
            append_node(&head, TOKEN_PIPE, "|");
            i++;
        }
        else if (input[i] == '$')
        {
            append_node(&head, TOKEN_DOLLAR, "$");
            i++;
        }
        else if (input[i] == '<' && input[i + 1] == '<')
        {
            append_node(&head, TOKEN_HEREDOC, "<<");
            i += 2;
        }
        else if (input[i] == '>' && input[i + 1] == '>')
        {
            append_node(&head, TOKEN_APPEND_OUTPUT, ">>");
            i += 2;
        }
        else if (input[i] == '<')
        {
            append_node(&head, TOKEN_INPUT, "<");
            i++;
        }
        else if (input[i] == '>')
        {
            append_node(&head, TOKEN_OUTPUT, ">");
            i++;
        }
        else if (ft_isalpha(input[i]) > 0)
        {
            start = i;
            while (input[i] && input[i] != ' ' && is_token(input[i]) != 1)
            {
                i++;
            }
            append_node(&head, TOKEN_WORD, ft_substr(input, start, i - start));
        }
        else
        {
            i++;
        }
    }
    // I need to put an end of file node / token at the end
    append_node(&head, TOKEN_EOF, NULL);

    return (head);
}
