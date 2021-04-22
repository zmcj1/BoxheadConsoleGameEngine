#pragma once

#include "MinDefines.h"
#include "Vector.h"
#include "Vector2.h"
#include "Random.h"
#include "Debug.h"
#include <vector>

namespace MinConsoleNative
{
    class MazeGenerator
    {
    private:
        static void LinkTo(Vector2& point, std::vector<Vector2>& availablePoints, std::vector<Vector2>& arrivedPoints, std::vector<Vector2>& routePoints)
        {
            std::vector<Vector2> canLinkPoints;

            if (Vector<Vector2>::Contains(availablePoints, point + Vector2::up * 2))
            {
                canLinkPoints.push_back(point + Vector2::up * 2);
            }
            if (Vector<Vector2>::Contains(availablePoints, point + Vector2::down * 2))
            {
                canLinkPoints.push_back(point + Vector2::down * 2);
            }
            if (Vector<Vector2>::Contains(availablePoints, point + Vector2::left * 2))
            {
                canLinkPoints.push_back(point + Vector2::left * 2);
            }
            if (Vector<Vector2>::Contains(availablePoints, point + Vector2::right * 2))
            {
                canLinkPoints.push_back(point + Vector2::right * 2);
            }

            if (!Vector<Vector2>::Contains(arrivedPoints, point))
            {
                Vector<Vector2>::Remove(availablePoints, point);
                arrivedPoints.push_back(point);
            }

            if (canLinkPoints.size() == 0)
            {
                Vector<Vector2>::Remove(arrivedPoints, point);
                if (arrivedPoints.size() == 0)
                {
                    return;
                }
                else
                {
                    int r = Random::Range(0, arrivedPoints.size() - 1);
                    Vector2 nextPos = arrivedPoints[r];
                    //Vector2 nextPos = arrivedPoints.front();
                    LinkTo(nextPos, availablePoints, arrivedPoints, routePoints);
                }
            }
            else
            {
                int r = Random::Range(0, canLinkPoints.size() - 1);
                Vector2 nextPos = canLinkPoints[r];
                //Break through the wall in the middle
                routePoints.push_back((point + nextPos) / 2);
                LinkTo(nextPos, availablePoints, arrivedPoints, routePoints);
            }
        }

    public:
        static std::vector<Vector2> GenerateKeyPoints(int width, int height)
        {
            std::vector<Vector2> keyPoints;
            for (int i = 1; i < height; i += 2)
            {
                for (int j = 1; j < width; j += 2)
                {
                    keyPoints.push_back(Vector2(j, i));
                }
            }
            return keyPoints;
        }

        //return:the positions of obstacles as a std::vector<Vector2>
        //NOTICE:width and height must be odd number!
        //NOTICE:The generation algorithm requires the length and width of the maze to be an odd number!
        static std::vector<Vector2> GenerateMaze(int width, int height)
        {
            if (width < 3 || height < 3)
            {
                throw "Invalid size!";
            }
            if (width % 2 != 1 || height % 2 != 1)
            {
                throw "The generation algorithm requires the length and width of the maze to be an odd number!";
            }

            std::vector<Vector2> emptyPositions;
            std::vector<Vector2> obstaclesPositions;

            std::vector<Vector2> availablePoints;   //key points here
            std::vector<Vector2> arrivedPoints;     //Points that have been visited
            std::vector<Vector2> routePoints;       //Beaten road

            emptyPositions = GenerateKeyPoints(width, height);
            availablePoints = emptyPositions;
            Vector2 startPos = availablePoints[Random::Range(0, availablePoints.size() - 1)];

            LinkTo(startPos, availablePoints, arrivedPoints, routePoints);

            for (int i = 0; i < routePoints.size(); i++)
            {
                emptyPositions.push_back(routePoints[i]);
            }

            for (size_t i = 0; i < height; i++)
            {
                for (size_t j = 0; j < width; j++)
                {
                    if (!Vector<Vector2>::Contains(emptyPositions, Vector2(j, i)))
                    {
                        obstaclesPositions.push_back(Vector2(j, i));
                    }
                }
            }

            return obstaclesPositions;
        }
    };
}