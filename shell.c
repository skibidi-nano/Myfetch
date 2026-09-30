#include "myfetch.h"
#include "shell.h"

int shell_fetch(void)
{
    char *shell = getenv("SHELL");
    char *shell_name;

    char * print_string;

    int text_y = TEXT_Y_INIT + SHELL_OFFSET;

    if (shell != NULL)
    {
        char *name = strrchr(shell, '/');
        if(*name == '/')
        {
            shell_name = name + 1;
        }
        else
        {
            shell_name = name;
        }

        print_string = "SHELL - ";
        mvprintw(text_y, TEXT_X, "%s", print_string);

        mvprintw(text_y, TEXT_X + strlen(print_string), "%s", shell_name);

        return 0;
    }
    else
    {
        return 1;
    }
}