#include "myfetch.h"
#include "meminfo.h"
#include "cpu_info.h"
#include "distro.h"
#include "host.h"
#include "disk.h"


int main(void)
{

    int cpu_check = 0;
    int distro_check = 0;
    int hostname_check = 0;
    int kernel_check = 0;
    int disk_check = 0;

    initscr();
    cbreak();
    noecho();

    //currently opened: meminfo
    int mem_fd = open("/proc/meminfo", O_RDONLY);
    if (mem_fd < 0) 
    {
        perror("ERROR: MemInfo file couldn't be accessed");
        return 2;
    }

    int cpu_fd = open("/proc/cpuinfo", O_RDONLY);
    if (cpu_fd < 0) 
    {
        perror("ERROR: CpuInfo file couldn't be accessed");
        close(mem_fd);
        return 2;
    }

    int distro_fd = open("/etc/os-release", O_RDONLY);
    if (distro_fd < 0) 
    {
        perror("ERROR: os-release file couldn't be accessed");
        close(mem_fd);
        close(cpu_fd);
        return 2;
    }

    int hostname_fd = open("/etc/hostname", O_RDONLY);
    if (hostname_fd < 0) 
    {
        perror("ERROR: hostname file couldn't be accessed");
        close(mem_fd);
        close(cpu_fd);
        close(distro_fd);
        return 2;
    }

    int kernel_fd = open("/proc/version", O_RDONLY);
    if (kernel_fd < 0)
    {
        perror("ERROR: version file couldn't be accessed");
        close(mem_fd);
        close(cpu_fd);
        close(distro_fd);
        close(hostname_fd);
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

        hostname_check = host_fetch(hostname_fd);
        if (hostname_check == 1)
        {
                perror("filesize detection error (hostname)"); 
                close(mem_fd);
                close(cpu_fd);
                close(distro_fd);
                close (hostname_fd);
                endwin();
                return 3;
        }
        else if (hostname_check == 2)
        {
                perror("error finding username "); 
                close(mem_fd);
                close(cpu_fd);
                close(distro_fd);
                close (hostname_fd);
                endwin();
                return 4;

        }

        kernel_check = kernel_fetch(kernel_fd);
        if (kernel_check == 1)
        {
                perror("filesize detection error (kernel version)"); 
                close(mem_fd);
                close(cpu_fd);
                close(distro_fd);
                close (hostname_fd);
                close(kernel_fd);
                endwin();
                return 3;
        }

        disk_check = disk_fetch();
        if (disk_check == 1)
        {
            perror("error with statvfs syscall"); 
            close(mem_fd);
            close(cpu_fd);
            close(distro_fd);
            close (hostname_fd);
            close(kernel_fd);
            endwin();
            return 3;

        }



        refresh();
        sleep(2);
    }

    
    
    close(mem_fd);
    close(cpu_fd);
    close(distro_fd);
    endwin();

    return 0;
}