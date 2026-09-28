#include "locale.h"
#include "myfetch.h"

int locale_fetch(int fd)
{
    char buffer[BUFFER_SIZE];
    char string_buffer[SECONDARY_BUFFER_SIZE]; //static value 
    char line_buffer[SECONDARY_BUFFER_SIZE]; //whole line
    int line_buffer_index = 0;
    char read_buffer[SECONDARY_BUFFER_SIZE]; //dynamic value (the things we are actually looking for)
    int read_buffer_index = 0;

    int strlength;
    int length_string_buffer;

    char* print_string; 
    int text_y = 0;

    lseek(fd, 0, SEEK_SET); // reset file descriptor

    parse_mapping mappings[] = 
    {
    //Codeword    Whats printed      y-offset
    //.key         .label        .offset
    {"LANG",    "Locale - ",      LOCALE_OFFSET},
    };
    int num_mappings = sizeof(mappings) / sizeof(mappings[0]);
    
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_read <= 0) 
    {
        return 1;
    }
    buffer[bytes_read] = '\0';

    for (int i = 0; i < bytes_read; i++)
    {
        line_buffer[line_buffer_index] = buffer[i];

        if(line_buffer[line_buffer_index] == '\n')
        {
            line_buffer[line_buffer_index] = '\0';
            line_buffer_index = 0;

            strlength = strlen(line_buffer);

            for (int j = 0; j < strlength; j++)
            {
                if (line_buffer[j] == '=')
                {
                    string_buffer[j] = '\0';
                    break;
                }
                else
                {
                    string_buffer[j] = line_buffer[j];
                }

            }

            for (int j = 0; j < num_mappings; j++)
            {
                if (!strcmp(string_buffer, mappings[j].key))
                {
                    strlength = (strlen(line_buffer) - strlen(string_buffer));
                    length_string_buffer = strlen(string_buffer);
                    for (int k = 0; k < strlength; k++)
                    {
                        if (line_buffer[k + length_string_buffer] != '=')
                        {
                            read_buffer[read_buffer_index] = line_buffer[k + length_string_buffer];
                            read_buffer_index++;
                        }
                        
                    }

                    read_buffer[read_buffer_index] = '\0';


                    offset = mappings[j].y_offset; //manipulte the global offset (maybe overall change the offset concept)
                    text_y = TEXT_Y_INIT + offset; // calculate the y variable


                    print_string = mappings[j].label;
                    mvprintw(text_y, TEXT_X, "%s", print_string);

                    mvprintw(text_y, TEXT_X + strlen(print_string), "%s", read_buffer);

                    read_buffer_index = 0;
                }
            }
        }
        else
        {
            line_buffer_index++;
        }
    }

    return 0;
}