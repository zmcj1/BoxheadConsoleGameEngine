#include "cengine.h"
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
float playerX;
float playerY;
float playerAngle;

float rotateSpeed;
float moveSpeed;

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

	clear(); //clean the screen

	//treak here
	const float deltaTime = 0.1f;

	while (1)
	{
		wait(deltaTime * 1000);
	}
	
	//destroy map:
	free(map);
	
	return 0;
}