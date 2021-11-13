#include "Maze.h"
#include "Vector.h"
#include "Random.h"

namespace MinConsoleNative
{
    void MazeGenerator::LinkTo(Vector2& point, std::vector<Vector2>& keyPoints, std::vector<Vector2>& arrivedPoints, std::vector<Vector2>& emptyPoints)
    {
        std::vector<Vector2> canLinkPoints;

        if (Vector<Vector2>::Contains(keyPoints, point + Vector2::up * 2))
        {
            canLinkPoints.push_back(point + Vector2::up * 2);
        }
        if (Vector<Vector2>::Contains(keyPoints, point + Vector2::down * 2))
        {
            canLinkPoints.push_back(point + Vector2::down * 2);
        }
        if (Vector<Vector2>::Contains(keyPoints, point + Vector2::left * 2))
        {
            canLinkPoints.push_back(point + Vector2::left * 2);
        }
        if (Vector<Vector2>::Contains(keyPoints, point + Vector2::right * 2))
        {
            canLinkPoints.push_back(point + Vector2::right * 2);
        }

        if (!Vector<Vector2>::Contains(arrivedPoints, point))
        {
            Vector<Vector2>::Remove(keyPoints, point);
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
                LinkTo(nextPos, keyPoints, arrivedPoints, emptyPoints);
            }
        }
        else
        {
            int r = Random::Range(0, canLinkPoints.size() - 1);
            Vector2 nextPos = canLinkPoints[r];
            //Break through the wall in the middle
            emptyPoints.push_back((point + nextPos) / 2);
            LinkTo(nextPos, keyPoints, arrivedPoints, emptyPoints);
        }
    }

    std::vector<Vector2> MazeGenerator::GenerateKeyPoints(int width, int height)
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

    std::vector<Vector2> MazeGenerator::GenerateMaze(int width, int height)
    {
        if (width < 3 || height < 3)
        {
            throw "Invalid size!";
        }
        if (width % 2 != 1 || height % 2 != 1)
        {
            throw "The generation algorithm requires the length and width of the maze to be an odd number!";
        }

        std::vector<Vector2> emptyPoints;
        std::vector<Vector2> obstaclesPoints;
        std::vector<Vector2> keyPoints;         //key points here
        std::vector<Vector2> arrivedPoints;     //Points that have been visited

        keyPoints = GenerateKeyPoints(width, height);
        emptyPoints = keyPoints;

        Vector2 startPos = keyPoints[Random::Range(0, keyPoints.size() - 1)];

#ifdef MAZE_USE_RECURSION
        LinkTo(startPos, keyPoints, arrivedPoints, emptyPoints);
#else
        Vector2 point = startPos;
        while (true)
        {
            std::vector<Vector2> canLinkPoints;

            if (Vector<Vector2>::Contains(keyPoints, point + Vector2::up * 2))
            {
                canLinkPoints.push_back(point + Vector2::up * 2);
            }
            if (Vector<Vector2>::Contains(keyPoints, point + Vector2::down * 2))
            {
                canLinkPoints.push_back(point + Vector2::down * 2);
            }
            if (Vector<Vector2>::Contains(keyPoints, point + Vector2::left * 2))
            {
                canLinkPoints.push_back(point + Vector2::left * 2);
            }
            if (Vector<Vector2>::Contains(keyPoints, point + Vector2::right * 2))
            {
                canLinkPoints.push_back(point + Vector2::right * 2);
            }

            //if this is a new point, add it!
            if (!Vector<Vector2>::Contains(arrivedPoints, point))
            {
                Vector<Vector2>::Remove(keyPoints, point);
                arrivedPoints.push_back(point);
            }

            //this is a dead point, backtracking to another point
            if (canLinkPoints.size() == 0)
            {
                Vector<Vector2>::Remove(arrivedPoints, point);
                if (arrivedPoints.size() == 0)
                {
                    break;
                }
                else
                {
                    int r = Random::Range(0, arrivedPoints.size() - 1);
                    Vector2 nextPos = arrivedPoints[r];
                    point = nextPos;
                }
            }
            else
            {
                int r = Random::Range(0, canLinkPoints.size() - 1);
                Vector2 nextPos = canLinkPoints[r];
                //Break through the wall in the middle
                emptyPoints.push_back((point + nextPos) / 2);
                point = nextPos;
            }
        }
#endif

        for (size_t i = 0; i < height; i++)
        {
            for (size_t j = 0; j < width; j++)
            {
                if (!Vector<Vector2>::Contains(emptyPoints, Vector2(j, i)))
                {
                    obstaclesPoints.push_back(Vector2(j, i));
                }
            }
        }

        return obstaclesPoints;
    }

    std::vector<Vector2> MazeGenerator::GenerateGround(const std::vector<Vector2>& maze, int width, int height)
    {
        std::vector<Vector2> ground;

        for (size_t i = 0; i < height; i++)
        {
            for (size_t j = 0; j < width; j++)
            {
                if (!Vector<Vector2>::Contains(maze, Vector2(j, i)))
                {
                    ground.push_back(Vector2(j, i));
                }
            }
        }

        return ground;
    }
}