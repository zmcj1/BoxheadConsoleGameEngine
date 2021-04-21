#pragma once

#include "MinDefines.h"
#include "Vector2.h"
#include <vector>
#include <queue>
#include <map>

namespace MinConsoleNative
{
    enum class SearchDirection
    {
        Four = 4,
        Eight = 8,
    };

    struct SearchNode
    {
    public:
        Vector2 position = Vector2::zero;
        SearchNode* preNode = nullptr;

        SearchNode(Vector2 position, SearchNode* preNode)
        {
            this->position = position;
            this->preNode = preNode;
        }
    };

    struct SearchResult
    {
    public:
        bool success = false;
        std::vector<SearchNode> searchedNodes;
        std::vector<SearchNode> path;
    };

    class Navigation
    {
    public:
        static SearchResult BFS(Vector2 startPos, Vector2 endPos, SearchDirection searchDir, int depthLimit, std::vector<Vector2>& obstacles)
        {
            SearchResult searchResult;
            //does't search...
            if (startPos == endPos) return searchResult;

            std::queue<SearchNode> searchingQueue;
            std::vector<SearchNode> searchedNodes;

            SearchNode startNode(startPos, nullptr);
            searchingQueue.push(startNode);
            searchedNodes.push_back(startNode);

            std::vector<Vector2> searchDirection;
            if (searchDir == SearchDirection::Four)
            {
                searchDirection.push_back(Vector2(0, 1));
                searchDirection.push_back(Vector2(0, -1));
                searchDirection.push_back(Vector2(1, 0));
                searchDirection.push_back(Vector2(-1, 0));
            }
            else if (searchDir == SearchDirection::Eight)
            {
                searchDirection.push_back(Vector2(0, 1));
                searchDirection.push_back(Vector2(0, -1));
                searchDirection.push_back(Vector2(1, 0));
                searchDirection.push_back(Vector2(-1, 0));
                searchDirection.push_back(Vector2(1, 1));
                searchDirection.push_back(Vector2(-1, -1));
                searchDirection.push_back(Vector2(1, -1));
                searchDirection.push_back(Vector2(-1, 1));
            }

            while (!searchingQueue.empty())
            {
                SearchNode currentNode = searchingQueue.front();
                searchingQueue.pop();

                bool success = false;

                for (size_t i = 0; i < searchDirection.size(); i++)
                {
                    Vector2 nextPosition = currentNode.position + searchDirection[i];

                    bool contains = false;
                    for (size_t j = 0; j < searchedNodes.size(); j++)
                    {
                        if (searchedNodes[i].position == nextPosition)
                        {
                            contains = true;
                            break;
                        }
                    }
                    if (contains)
                    {
                        continue;
                    }

                    bool nextPositionIsObstacle = false;
                    for (size_t i = 0; i < obstacles.size(); i++)
                    {
                        if (obstacles[i] == nextPosition)
                        {
                            nextPositionIsObstacle = true;
                            break;
                        }
                    }
                    if (nextPositionIsObstacle)
                    {
                        continue;
                    }

                    SearchNode nextNode(nextPosition, &currentNode);
                    searchedNodes.push_back(nextNode);
                    //search success
                    if (nextPosition == endPos)
                    {
                        success = true;
                        break;
                    }
                    else
                    {
                        searchingQueue.push(nextNode);
                    }
                }

                if (success)
                {
                    break;
                }
            }

            searchResult.success = true;
            searchResult.searchedNodes = searchedNodes;
            std::vector<SearchNode*> tempVector;

            SearchNode* node_ptr = &searchedNodes[searchedNodes.size() - 1];
            tempVector.push_back(node_ptr);
            while (node_ptr->preNode != nullptr)
            {
                node_ptr = node_ptr->preNode;
                tempVector.push_back(node_ptr);
            }
            //reverse
            for (int i = tempVector.size() - 1; i >= 0; i--)
            {
                searchResult.path.push_back(*tempVector[i]);
            }

            return searchResult;
        }
    };
}