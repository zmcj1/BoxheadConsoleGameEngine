#ifndef CENGINE_H
#define CENGINE_H
//linux only
#ifdef __linux__
//include header files:
#include <stdio.h>  //printf
//defines:
#define ESC "\033"  //00011011 = 033 = 27 = 0x1B

inline void setforecolor(int r, int g, int b)
{
	printf("%s[38;2;%d;%d;%dm", ESC, r, g, b);
}

inline void setbackcolor(int r, int g, int b)
{
	printf("%s[48;2;%d;%d;%dm", ESC, r, g, b);
}

inline void resetcolor()
{
	printf("%s[0m", ESC);
}

inline void clear()
{
	printf("%sc", ESC);
}

#endif
#endif