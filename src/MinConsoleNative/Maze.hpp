#pragma once

#include "MinDefines.hpp"
#include "Vector2.hpp"
#include <vector>

namespace MinConsoleNative
{
    class MazeGenerator
    {
    private:
        MazeGenerator()
        {
        }

        static void LinkTo(Vector2& point, std::vector<Vector2>& keyPoints, std::vector<Vector2>& arrivedPoints, std::vector<Vector2>& emptyPoints);

    public:
        static std::vector<Vector2> GenerateKeyPoints(int width, int height);

        //return:the positions of obstacles as a std::vector<Vector2>
        //NOTICE:The generation algorithm requires the length and width of the maze to be an odd number!(3, 5, 7, 9, 11, 13, 15...)
        static std::vector<Vector2> GenerateMaze(int width, int height);

        //根据迷宫获取空地
        static std::vector<Vector2> GenerateGround(const std::vector<Vector2>& maze, int width, int height);
    };
}