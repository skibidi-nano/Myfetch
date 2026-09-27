#include "meminfo.h"
#include "myfetch.h"

void memory_fetch(int fd)
{
    char buffer[BUFFER_SIZE];
    static char string_buffer[SECONDARY_BUFFER_SIZE]; //buffer for comparison of strings
    int str_buffer_index = 0;
    static char number_buffer[SECONDARY_BUFFER_SIZE]; //buffer for calculating size
    int nmbr_buffer_index = 0;
    bool number_write_check = false; //to check if you want to write the numbers
    
    char* print_string;

    int text_y = 0;
    

    
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1); //read /proc/meminfo into the buffer (we only need to read once)
    if (bytes_read <= 0) 
    { //check for errors
        return;
    }
    buffer[bytes_read] = '\0';
   

    parse_mapping mappings[] = 
    {
    //Codeword    Whats printed      y-offset
    //.key         .label        .offset
    {"MemTotal",  "Total memory - ", MEM_TOTAL_OFFSET},
    {"MemFree",   "Free memory - ",  MEM_FREE_OFFSET},
    {"Cached",    "Cached memory - ",CACHED_OFFSET},
    {"SwapTotal", "Total swap - ",   SWAP_TOTAL_OFFSET},
    {"SwapFree",  "Free swap - ",    SWAP_FREE_OFFSET}
    };

    int num_mappings = sizeof(mappings) / sizeof(mappings[0]);


    for (int i = 0; i < bytes_read; i++)
    {
        if (isalpha(buffer[i]))
        {
            string_buffer[str_buffer_index] = buffer[i];
            str_buffer_index++;
        }
        else if(buffer[i] == ':')
        {
            string_buffer[str_buffer_index] = '\0';
            
            //check for specfics rest inst used
            for (int j = 0; j < num_mappings; j++)
            {
                if (!strcmp(string_buffer, mappings[j].key))
                {
                    offset = mappings[j].y_offset; //manipulte the global offset (maybe overall change the offset concept)
                    text_y = TEXT_Y_INIT + offset; // calculate the y variable

                    print_string = mappings[j].label; //create the string (extra variable for size offset)

                    number_write_check = true;

                    mvprintw(text_y, TEXT_X, "%s", mappings[j].label);

                    break;
                }
            }   
        }
        else if(buffer[i] == '\n')
        {
            number_buffer[nmbr_buffer_index] = '\0'; //terminate the text
            str_buffer_index = 0; //reset buffers
            nmbr_buffer_index = 0; //////////////

            double number_value = atol(number_buffer); //convert the read string to a number
            number_value /= 1024 * 1024; // convert to GiB (i think)
            if(number_write_check)
            {
                mvprintw(text_y, TEXT_X + strlen(print_string), "%.2f GiB", number_value);
            }

            number_write_check = false; //reset the writing check
        }
        
        if(isdigit(buffer[i]) && number_write_check)
        {
            number_buffer[nmbr_buffer_index] = buffer[i]; //buffer the variable
            nmbr_buffer_index++; //move on to the next buffer
        }
    }
}