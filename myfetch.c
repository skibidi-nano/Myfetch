#include "myfetch.h"
#include "meminfo.h"
#include "cpu_info.h"
#include "distro.h"
#include "host.h"
#include "disk.h"
#include "locale.h"

file_descriptor fd;

int main(void)
{

    int cpu_check = 0;
    int distro_check = 0;
    int hostname_check = 0;
    int kernel_check = 0;
    int disk_check = 0;
    int locale_check = 0;

    initscr();
    cbreak();
    noecho();

    fd.mem = open("/proc/meminfo", O_RDONLY);
    if (fd.mem < 0) 
    {
        perror("ERROR: MemInfo file couldn't be accessed");
        return 2;
    }

    fd.cpu = open("/proc/cpuinfo", O_RDONLY);
    if (fd.cpu < 0) 
    {
        perror("ERROR: CpuInfo file couldn't be accessed");
        close(fd.mem);
        return 2;
    }

    fd.distro = open("/etc/os-release", O_RDONLY);
    if (fd.kernel < 0) 
    {
        perror("ERROR: os-release file couldn't be accessed");
        close(fd.mem);
        close(fd.cpu);
        return 2;
    }

    fd.hostname = open("/etc/hostname", O_RDONLY);
    if (fd.hostname < 0) 
    {
        perror("ERROR: hostname file couldn't be accessed");
        close(fd.mem);
        close(fd.cpu);
        close(fd.distro);
        return 2;
    }

    fd.kernel = open("/proc/version", O_RDONLY);
    if (fd.kernel < 0)
    {
        perror("ERROR: version file couldn't be accessed");
        cleanup();
        return 2;
    }

    fd.locale = open("/etc/locale.conf", O_RDONLY);
    if (fd.locale < 0) 
    {
        perror("ERROR: locale.conf file couldn't be accessed");
        close(fd.mem);
        close(fd.cpu);
        close(fd.distro);
        close (fd.hostname);
        close(fd.kernel);
        return 2;
    }

    while (true)
    {
        clear();
        if (lseek(fd.mem, 0, SEEK_SET) == (off_t)-1) {
            perror("lseek failed");
            break;
        }

        memory_fetch(fd.mem);

        cpu_check = cpu_fetch(fd.cpu);
        if (cpu_check == 1)
        {
            perror("filesize detection error (cpuinfo)"); 
            cleanup();
            return 3;
        }

        distro_check = distro_fetch(fd.distro);
        if (distro_check == 1)
        {
            perror("filesize detection error (os-release)"); 
            cleanup();
            return 3;
        }

        hostname_check = host_fetch(fd.hostname);
        if (hostname_check == 1)
        {
            perror("filesize detection error (hostname)"); 
            cleanup();
            return 3;
        }
        else if (hostname_check == 2)
        {
            perror("error finding username "); 
            cleanup();
            return 4;

        }

        kernel_check = kernel_fetch(fd.kernel);
        if (kernel_check == 1)
        {
            perror("filesize detection error (kernel version)"); 
            cleanup();
            return 3;
        }

        disk_check = disk_fetch();
        if (disk_check == 1)
        {
            perror("error with statvfs syscall"); 
            cleanup();
            return 3;

        }

        locale_check = locale_fetch(fd.locale);
        if (locale_check == 1)
        {
            perror("filesize detection error (locale.conf)"); 
            cleanup();
            return 3;

        }

        refresh();
        sleep(2);
    }

    
    
    cleanup();
    return 0;
}

void cleanup(void)
{
    close(fd.mem);
    close(fd.cpu);
    close(fd.distro);
    close (fd.hostname);
    close(fd.kernel);
    close(fd.locale);
    endwin();
}