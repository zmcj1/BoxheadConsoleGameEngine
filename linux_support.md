This file is created in Ubuntu Desktop.

PS:It's hard to program in Linux Terminal without using the ncurses.

Ncurses HOWTO:
https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/index.html

Plan(TODO):

1. Make a [C/C++ header file](https://github.com/OpenGreatDream/MinConsole/blob/main/linux/cengine.h) for supporting linux terminal.(GNOME Terminal on Ubuntu 20.04)
    1. <del>24-bit fore/back color support</del>
    2. simple timer support
    3. input function like GetAsyncKeyState
    4. fast and partial(optimized) output