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
        static void LinkTo(Vector2& current, std::vector<Vector2>& availablePos, std::vector<Vector2>& arrivedPos, std::vector<Vector2>& routePos)
        {
            std::vector<Vector2> canLinkPos;

            if (Vector<Vector2>::Contains(availablePos, current + Vector2::up * 2))
            {
                canLinkPos.push_back(current + Vector2::up * 2);
            }
            if (Vector<Vector2>::Contains(availablePos, current + Vector2::down * 2))
            {
                canLinkPos.push_back(current + Vector2::down * 2);
            }
            if (Vector<Vector2>::Contains(availablePos, current + Vector2::left * 2))
            {
                canLinkPos.push_back(current + Vector2::left * 2);
            }
            if (Vector<Vector2>::Contains(availablePos, current + Vector2::right * 2))
            {
                canLinkPos.push_back(current + Vector2::right * 2);
            }

            if (!Vector<Vector2>::Contains(arrivedPos, current))
            {
                Vector<Vector2>::Remove(availablePos, current);
                arrivedPos.push_back(current);
            }

            if (canLinkPos.size() == 0)
            {
                Vector<Vector2>::Remove(arrivedPos, current);

                if (arrivedPos.size() == 0) return;
                else
                {
                    int r = Random::Range(0, arrivedPos.size() - 1);
                    LinkTo(arrivedPos[r], availablePos, arrivedPos, routePos);
                }
            }
            else
            {
                int r = Random::Range(0, canLinkPos.size() - 1);
                Vector2 nextPos = canLinkPos[r];
                routePos.push_back((current + nextPos) / 2);
                LinkTo(nextPos, availablePos, arrivedPos, routePos);
            }
        }

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

            LinkTo(startPos, availablePos, arrivedPos, routePos);

            for (int i = 0; i < routePos.size(); i++)
            {
                pathPositions.push_back(routePos[i]);
            }

            return pathPositions;
        }
    };
}