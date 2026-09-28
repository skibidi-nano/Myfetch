#include "host.h"
#include "myfetch.h"

int host_fetch(int fd)
{
    char buffer[BUFFER_SIZE];
    char read_buffer[SECONDARY_BUFFER_SIZE];
    int read_buffer_index = 0;
    char *print_string;
    int text_y = TEXT_Y_INIT + HOSTNAME_OFFSET;
    
    uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);

    lseek(fd, 0, SEEK_SET); // reset file descriptor

    ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_read <= 0) 
    {
      return 1;
    }
    buffer[bytes_read] = '\0';

    for (int i = 0; i < bytes_read; i++)
    {
        read_buffer[read_buffer_index] = buffer[i];
        read_buffer_index++;
    }

    read_buffer[read_buffer_index] = '\0';


    print_string = "Hostname - ";
    mvprintw(text_y, TEXT_X, "%s", print_string);

    if (pw) 
    {
        mvprintw(text_y, TEXT_X + strlen(print_string), "%s@%s", pw->pw_name, read_buffer);
    } 
    else 
    {
        return 2;
    }

    mvprintw(text_y + 1, TEXT_X, "~~~~~");

    return 0;
}