#include "helper.h"
#include "myfetch.h"

long long get_file_size_stat(int fd)
{

    char buffer[256];
    ssize_t total_bytes = 0;
    ssize_t bytes_read;

    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        total_bytes += bytes_read;
    }

    if (bytes_read < 0) {
        return -1;
    }

    return total_bytes;
    
}