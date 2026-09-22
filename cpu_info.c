#include "cpu_info.h"
#include "myfetch.h"

void cpu_info(int fd)
{
    char buffer[BUFFER_SIZE];
    static char string_buffer[32]; //will change from magic number
    static char number_buffer[32];
    int nmbr_buffer_index = 0;
    int str_buffer_index = 0;
    bool number_write_check = false;

    ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);

    if (bytes_read <= 0) {
        return;
    }
    buffer[bytes_read] = '\0';

    for (int i = 0; i < bytes_read; i++)
    {
        if (isalnum(buffer[i]))
        {
            string_buffer[str_buffer_index] = buffer[i];
            str_buffer_index++;
        }
        else if(buffer[i] == ' ' && buffer[i - 1] != ' ')
        {
            if (!strcmp(string_buffer, "model name"))
            {
                number_write_check = true;
                printf("Model name - ");
            }
        }
        else if(buffer[i] == '\n')
        {
            number_buffer[nmbr_buffer_index] = '\0';
            str_buffer_index = 0;
            nmbr_buffer_index = 0;

            double number_value = atol(number_buffer);
            number_value /= 1024 * 1024;
            if(number_write_check)
            {
                printf("%.2f GiB", number_value);
                printf("\n");
            }

            number_write_check = false;
        }
        
        if(isdigit(buffer[i]) && number_write_check)
        {
            number_buffer[nmbr_buffer_index] = buffer[i];
            nmbr_buffer_index++;
        }
    }
}