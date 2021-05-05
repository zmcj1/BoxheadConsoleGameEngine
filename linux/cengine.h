#ifndef CENGINE_H
#define CENGINE_H
//linux only
#ifdef __linux__
//include header files:
#include <stdio.h>  //printf
#include <unistd.h> //usleep(microSecond)

//defines:
#define ESC "\033"  //00011011 = 033 = 27 = 0x1B

//typedefs:
typedef unsigned int uint; //uint32
typedef unsigned short ushort; //ushort32
typedef unsigned char byte; //range:0-255

//structures:
typedef struct
{
	byte r;
	byte g;
	byte b;
} Color24;

typedef struct
{
	int x;
	int y;
} Vec2;

typedef struct
{
	union
	{
		char AsciiChar;
	} Char;
	Color24 foreColor;
	Color24 backColor;
} CHAR_INFO;

//inline functions:
inline Vec2 make_vec2(int x, int y)
{
	Vec2 vec2 = {x, y};
	return vec2;
}

inline void gotoxy(int x, int y)
{
	printf("%s[%d;%dH", ESC, y+1, x+1);
}

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

inline void wait(uint milliSecond)
{
	//SEE:https://linux.die.net/man/3/usleep
	//microSecond -> milliSecond
	usleep(milliSecond * 1000);
}

inline void draw(const CHAR_INFO* ci)
{
	setforecolor(ci->foreColor.r, ci->foreColor.g, ci->foreColor.b);
	setbackcolor(ci->backColor.r, ci->backColor.g, ci->backColor.b);
	printf("%c", ci->Char.AsciiChar);
	resetcolor();
}

inline void drawxy(const CHAR_INFO* ci, int x, int y)
{
	gotoxy(x, y);
	draw(ci);
}

#endif
#endif