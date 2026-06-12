#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
	char	*line;

	while (1)
	{
		int			i;

		line = readline("playground> ");
		if (line == NULL)
			break;

		if (line != NULL)
			add_history(line); // 1)

		if (strcmp(line, "exit") == 0)
		{
			free(line);
			break;
		}

		i = 0;
		if (strcmp(line, "history") == 0)
		{
			HIST_ENTRY **list = history_list();
			while (list && list[i])
			{
				printf("%d: %s\n", i, list[i]->line);
				i++;
			}
		}

		else if (strcmp(line, "clear") == 0)
		{
			rl_clear_history(); // 2)
			printf("history cleared\n");
		}

		else if (strcmp(line, "replace") == 0)
		{
			rl_on_new_line(); // 3)
			rl_replace_line("REPLACED TEXT", 1); //4)
			rl_redisplay(); // 5)
			printf("\n");
		}

		else
			printf("you typed: %s\n", line);

		free(line);
	}
	return (0);
}
