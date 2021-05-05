#include <ncurses.h> //ncurses lib
#include <unistd.h> //usleep(microSecond)
#include <stdio.h> //printf
#include <stdlib.h> //malloc
#include <string.h> //strncat

//the width and height of terminal
int consoleWidth = 60;
int consoleHeight = 30;

//map
char* map;
const int mapWidth = 10;
const int mapHeight = 10;

//player:
float playerX = 2.0f;
float playerY = 4.0f;
float playerAngle = 0.0f;

float rotateSpeed = 3.14159f;
float moveSpeed = 5.0f;

const float FOV = 3.14159 / 4;
const float depth = 10;

int main()
{
	//creat map:
	map = (char*)malloc(sizeof(char) * mapWidth * mapHeight);
	if (map == NULL)
	{
		printf("Alloc map failed!");
		return -1;
	}
	strncat(map, "##########", mapWidth+1);
	strncat(map, "#        #", mapWidth+1);
	strncat(map, "#        #", mapWidth+1);
	strncat(map, "###      #", mapWidth+1);
	strncat(map, "###      #", mapWidth+1);
	strncat(map, "#####  ###", mapWidth+1);
	strncat(map, "#####  ###", mapWidth+1);
	strncat(map, "#        #", mapWidth+1);
	strncat(map, "#        #", mapWidth+1);
	strncat(map, "##########", mapWidth+1);

	initscr(); //init the screen
	raw();
	noecho(); //disable echo
	
	//treak here :)
	const float deltaTime = 0.1f;

	while (1)
	{
		int c = getch();
		if (c == 'a')
		{
			addch('a');
			refresh();
		}
		usleep(deltaTime * 1000000);
	}

	endwin(); //close the screen
	
	//destroy map:
	free(map);
	
	return 0;
}