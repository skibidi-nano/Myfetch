#include "disk.h"
#include "myfetch.h"

int disk_fetch(void)
{
    struct statvfs vfs;
    int text_y = 0;
    char *print_string;
    double total_bytes = 0;


    if (statvfs("/", &vfs) == 0) 
    {
        text_y = TEXT_Y_INIT + DISK_OFFSET;
        print_string = "Max space - ";
        mvprintw(text_y, TEXT_X, "%s", print_string);
        total_bytes = (double)vfs.f_blocks * vfs.f_frsize;
        double total_space = total_bytes / 1073741824.0;
        mvprintw(text_y, TEXT_X + strlen(print_string), "%.2f GiB", total_space);

        
        text_y = TEXT_Y_INIT + AVAILABLE_DISK_OFFSET;
        print_string = "Available space - ";
        mvprintw(text_y, TEXT_X, "%s", print_string);
        total_bytes = (double)vfs.f_bavail * vfs.f_frsize;
        double current_space = total_bytes / 1073741824.0;
        mvprintw(text_y, TEXT_X + strlen(print_string), "%.2f GiB", current_space);
    }
    else
    {
        return 1;
    }

    return 0;
}