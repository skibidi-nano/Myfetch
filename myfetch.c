#include "myfetch.h"
#include "meminfo.h"


int main(void)
{

    //currently opened: meminfo
    int mem_fd = open("/proc/meminfo", O_RDONLY);
    if (mem_fd < 0) 
    {
        printf("ERRROR: MemInfo fike couldn't be accessed");
        return 1;
    }

    int cpu_fd = open("/proc/cpuinfo", O_RDONLY);
    if (cpu_fd < 0) 
    {
        printf("ERRROR: CPUInfo fike couldn't be accessed");
        return 1;
    }

    memory_fetch(mem_fd);
    cpu_fetch(cpu_fd);


    
    close(mem_fd);
    close(cpu_fd);
    return 0;
}