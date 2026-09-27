#ifndef MYFETCH_H
#define MYFETCH_H

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <ncurses.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>


static int offset = 0;
typedef struct {
    char *key;
    char *label;
    int y_offset;
} parse_mapping;


#define BUFFER_SIZE 2048
#define SECONDARY_BUFFER_SIZE 512
#define TEXT_X 45
#define TEXT_X_STATIC 45
#define TEXT_X_DYNAMIC 60
#define TEXT_Y_INIT 5
#define ASCII_COORD_Y 5
#define ASCII_COORD_X 4

#define HOSTNAME_OFFSET 0
#define PRETTY_NAME_OFFSET 2
#define KERNEL_OFFSET 3
#define MODEL_NAME_OFFSET 4
#define PROCESSOR_OFFSET 5
#define MEM_TOTAL_OFFSET 6
#define MEM_FREE_OFFSET 7
#define CACHED_OFFSET 8
#define SWAP_TOTAL_OFFSET 9
#define SWAP_FREE_OFFSET 10
#define DISK_OFFSET 11
#define AVAILABLE_DISK_OFFSET 12

#define NO_OFFSET 0



#endif