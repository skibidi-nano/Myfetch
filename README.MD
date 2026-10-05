# !! MYFETCH, MY FETCHING PROGRAM FOR ME AN YOU !!

## A FETCHING PROGRAM COMPLETELY BUILT IN C THAT TRACKS LIVE STATS

![demo.png](/pictures/demo.png)

## KEY FEATURES

Displays the following:
- Host and username
- OS and OS Version
- Current kernel version
- Processor name
- Amount of threads
- Total amount and cached amount of RAM and swap
- Total and available disk space
- The systemlocale
- The current uptime
- Your local IP (IPv4) !! NOTE: its your first non-loopback IPv4 address !!
- The shell you are using
- A distro-specific ASCII logo (with a generic fallback for unsupported distros).

## How build/use

### Build tutorial (if you do not use the precompiled version)

You will need the following packages:
  - clang
  - gnumake
  - ncurses

NOTE: 
- If on nixos you can use my shell.nix also in the project files
- ALSO if precompiled build fails (probably because your ncurses is on a newer verson, normal for rolling release distros), you will need to compile it yourself.
- Build was tested on fedora and nixos

The Makefile is included. Move into the project folder:

    make main
    ./main

To clean up build artifacts:

    make clean

## PROJECT STRUCTURE

- myfetch.c         - Main loop of the program, opening and closing file descriptors
- myfetch.h         - "Library for other libraries", offsets, macros for buffer sizes
- host.c/.h         - Looking up hostname and username
- cpu_info.c/.h     - Looking up info about the cpu
- distro.c/.h       - Collect info about your distro/kernel version, ASCII's
- meminfo.c/.h      - Tracking live info about your ram usage etc.
- disk.c/.h         - Tracking free and total space
- locale.c/.h       - Looking up the LANG= locale
- ip.c/.h           - Finding your ip
- shell.c/.h        - Finding your current shell
- helper.c/.h       - Responsible for some misc functions used all across the program

## STATUS

Build isn't fully polished. Bugs may occur. There are no known crashes, but things can still not work as intended.

## LICENSE

MIT (see license file)
