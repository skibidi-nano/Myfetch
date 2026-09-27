#include "myfetch.h"
#include "meminfo.h"
#include "cpu_info.h"
#include "logo.h"


int main(void)
{

    int cpu_check = 0;
    int distro_check = 0;
    initscr();
    cbreak();
    noecho();

    //currently opened: meminfo
    int mem_fd = open("/proc/meminfo", O_RDONLY);
    if (mem_fd < 0) 
    {
        perror("ERRROR: MemInfo file couldn't be accessed");
        return 2;
    }

    int cpu_fd = open("/proc/cpuinfo", O_RDONLY);
    if (cpu_fd < 0) 
    {
        perror("ERRROR: CpuInfo file couldn't be accessed");
        close(mem_fd);
        return 2;
    }

    int distro_fd = open("/etc/os-release", O_RDONLY);
    if (distro_fd < 0) 
    {
        perror("ERRROR: os-release file couldn't be accessed");
        close(mem_fd);
        close(cpu_fd);
        return 2;
    }

    while (true)
    {
        if (lseek(mem_fd, 0, SEEK_SET) == (off_t)-1) {
            perror("lseek failed");
            break;
        }

        memory_fetch(mem_fd);

        cpu_check = cpu_fetch(cpu_fd);
        if (cpu_check == 1)
        {
                perror("filesize detection error (cpuinfo)"); 
                close(mem_fd);
                close(cpu_fd);
                endwin();
                return 3;
        }

        distro_check = distro_fetch(distro_fd);
        if (distro_check == 1)
        {
                perror("filesize detection error (os-release)"); 
                close(mem_fd);
                close(cpu_fd);
                close(distro_fd);
                endwin();
                return 3;
        }

        refresh();
        sleep(2);
    }

    
    
    close(mem_fd);
    close(cpu_fd);
    close(distro_fd);
    int user_input = 0;
    if ((user_input = getchar()) > 0)
    {
        endwin();
    }    
    return 0;
}