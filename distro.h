#include "myfetch.h"

int kernel_fetch(int fd);
int distro_fetch(int fd);

void distro_ascii(char *distro);

char **nixos_ascii(void);
char **debian_ascii(void);
char **arch_ascii(void);
char **ubuntu_ascii(void);
char **gentoo_ascii(void);

char **unsupported_ascii(void);