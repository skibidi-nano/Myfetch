#include "myfetch.h"

int distro_fetch(int fd);

void distro_ascii(char *distro);

char **nixos_ascii(void);
char **debian_ascii(void);
char **arch_ascii(void);