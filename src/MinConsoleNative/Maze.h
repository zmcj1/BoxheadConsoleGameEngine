#pragma once

#include "MinDefines.h"
#include "Vector2.h"
#include "Random.h"
#include "Debug.h"
#include <vector>

namespace MinConsoleNative
{
    class MazeGenerator
    {
    public:


        static std::vector<Vector2> GenerateMaze(int width, int height)
        {
            std::vector<Vector2> pathPositions;

            if (height % 2 != 1 || width % 2 != 1)
            {
                Debug::OutputLine(L"The generation algorithm requires the length and width of the maze to be an odd number!");
                return pathPositions;
            }

            std::vector<Vector2> availablePos;
            for (int i = 1; i < height; i += 2)
            {
                for (int j = 1; j < width; j += 2)
                {
                    availablePos.push_back(Vector2(j, i));
                    pathPositions.push_back(Vector2(j, i));
                }
            }

            std::vector<Vector2> arrivedPos;
            std::vector<Vector2> routePos;

            Vector2 startPos = availablePos[Random::Range(0, availablePos.size() - 1)];

            auto func = [](Vector2 current)
            {
                std::vector<Vector2> canLinkPos;


            };

            func(startPos);

            for (int i = 0; i < routePos.size(); i++)
            {
                pathPositions.push_back(routePos[i]);
            }

            return pathPositions;
        }
    };
}