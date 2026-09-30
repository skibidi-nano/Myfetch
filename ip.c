#include <ifaddrs.h>
#include <arpa/inet.h> 
#include "myfetch.h"
#include "ip.h"


void ip_fetch(void)
{
    struct ifaddrs *ifaddr = NULL;
    struct ifaddrs *ifa = NULL;
    char ip_str[INET_ADDRSTRLEN]; 
    char *print_string;
    int text_y = TEXT_Y_INIT + IP_OFFSET;

    if (getifaddrs(&ifaddr) == -1) 
    {
        mvprintw(TEXT_Y_INIT, TEXT_X, "Error finding interfaces");
        return;
    }

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) 
    {
        
        if (ifa->ifa_addr == NULL) {
            continue;
        }
        if (ifa->ifa_addr->sa_family != AF_INET) 
        {
            continue;
        }
        if (!strcmp(ifa->ifa_name, "lo")) 
        {
            continue;
        } 
            
        struct sockaddr_in *sa = (struct sockaddr_in *)ifa->ifa_addr;
                  
        inet_ntop(AF_INET, &(sa->sin_addr), ip_str, INET_ADDRSTRLEN);
            
        print_string = "IPV4 - ";
        mvprintw(text_y, TEXT_X, "%s", print_string);

        mvprintw(text_y, TEXT_X + strlen(print_string), "%s", ip_str);
    }

    freeifaddrs(ifaddr);
}