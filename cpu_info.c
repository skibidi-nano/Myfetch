#include "cpu_info.h"
#include "myfetch.h"
#include "helper.h"

int cpu_fetch(int fd)
{
    float size_buffer = BUFFER_SIZE;
    char buffer[BUFFER_SIZE];
    char string_buffer[SECONDARY_BUFFER_SIZE]; //static value 
    char line_buffer[SECONDARY_BUFFER_SIZE]; //whole line
    char read_buffer[SECONDARY_BUFFER_SIZE]; //dynamic value (the things we are actually looking for)
    int line_buffer_index = 0;
    int strlength;
    int length_string_buffer;

    char* print_string; 
    int text_y = 0;

    parse_mapping mappings[] = 
    {
    //Codeword    Whats printed      y-offset
    //.key         .label        .offset
    {"processor\t:",    "Threads - ",      PROCESSOR_OFFSET},
    {"model name\t:",   "Processor -",  MODEL_NAME_OFFSET},
    };
    int num_mappings = sizeof(mappings) / sizeof(mappings[0]);

    static long long filesize;
    filesize = get_file_size_stat(fd);
    lseek(fd, 0, SEEK_SET); // reset file descriptor
    if (filesize == -1)
    {
        return 1;
    }

    double iterations = ceil(filesize / size_buffer);
    for (int iteration = 0; iteration < iterations; iteration++)
    {
        //lseek(fd, 0, SEEK_SET); // reset file descriptor
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
                    string_buffer[j] = line_buffer[j];

                    if(string_buffer[j] == ':')
                    {
                        string_buffer[j] = line_buffer[j];
                        string_buffer[j + 1] = '\0';
                        break;
                    }
                }
                

                for (int j = 0; j < num_mappings; j++)
                {

                    if(!strcmp(string_buffer, mappings[j].key))
                    {
                        strlength = (strlen(line_buffer) - strlen(string_buffer));
                        length_string_buffer = strlen(string_buffer);
                        for (int k = 0; k < strlength; k++)
                        {
                            read_buffer[k] = line_buffer[k + length_string_buffer];
                        }

                        read_buffer[strlength] = '\0';


                            offset = mappings[j].y_offset; //manipulte the global offset (maybe overall change the offset concept)
                            text_y = TEXT_Y_INIT + offset; // calculate the y variable


                        print_string = mappings[j].label;
                        mvprintw(text_y, TEXT_X, "%s", print_string);

                        if (!strcmp(mappings[j].label, "Threads - "))
                        {
                            int cores = atoi(read_buffer); 
                            cores++;
                            mvprintw(text_y, TEXT_X + strlen(print_string), "%i", cores);
                        }
                        else
                        {
                            mvprintw(text_y, TEXT_X + strlen(print_string), "%s", read_buffer);
                        }
                            
                    }
                }
            }
            else
            {
                line_buffer_index++;
            }
                
        }
    }
    

    return 0;
    
}