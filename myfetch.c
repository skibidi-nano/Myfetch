#include "myfetch.h"


int main(void)
{

    
    char buffer[2048];

    //currently opened: meminfo
    int fd = open("/proc/meminfo", O_RDONLY);

    if (fd < 0) 
    {
        printf("ERRROR: MemInfo fike couldn't be accessed");
        return 1;
    }
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);

    if (bytes_read > 0) 
    {
        buffer[bytes_read] = '\0';
    }
    close(fd);





    return 0;
}