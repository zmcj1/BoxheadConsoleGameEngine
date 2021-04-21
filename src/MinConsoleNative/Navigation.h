#pragma once

#include "MinDefines.h"
#include "Vector2.h"
#include <vector>

namespace MinConsoleNative
{
    enum class SearchDirection
    {
        Four = 4,
        Eight = 8,
    };

    enum class SearchMethod
    {
        BFS = 1,
        DFS = 2,
    };

    struct Node
    {
    public:
        Vector2 position;   //position of this node
        int depth;          //distance to the origin position(Obstacles have been considered).

        Node(Vector2 position, int depth)
        {
            this->position = position;
            this->depth = depth;
        }
    };

    struct SearchResult
    {
    public:
        bool success = false;
        std::vector<Node> searchedNodes;    //All searched nodes
        std::vector<Node> path;             //The result of pathfinding includes the starting point and the ending point
    };

    class Navigation
    {
    private:
        struct SearchNode
        {
        public:
            Vector2 position = Vector2::zero;
            int depth = 0;
            SearchNode* preNode = nullptr;

            SearchNode(Vector2 position, int depth, SearchNode* preNode)
            {
                this->position = position;
                this->depth = depth;
                this->preNode = preNode;
            }
        };

        static bool ContainsPosition(const std::vector<Vector2>& container, const Vector2& element)
        {
            for (int i = 0; i < container.size(); i++)
            {
                if (container[i] == element) return true;
            }
            return false;
        }

        static bool ContainsPosition(const std::vector<SearchNode*>& container, const Vector2& element)
        {
            for (int i = 0; i < container.size(); i++)
            {
                if (container[i]->position == element) return true;
            }
            return false;
        }

    public:
        //calculate when SearchDirection == SearchDirection::Four
        //input:depth(Number of searches) output:Number of nodes searched
        static int BFS4_Depth(int depth)
        {
            if (depth < 1) return 1;
            //Arithmetic sequence
            return (4 + 4 * depth) * depth / 2 + 1;
        }

        //calculate when SearchDirection == SearchDirection::Eight
        //input:depth(Number of searches) output:Number of nodes searched
        static int BFS8_Depth(int depth)
        {
            if (depth < 1) return 1;
            return (2 * depth + 1) * (2 * depth + 1);
        }

        static SearchResult Navigate(Vector2 startPos, Vector2 endPos, SearchDirection searchDir, int depthLimit, std::vector<Vector2>& obstacles, SearchMethod searchMethod)
        {
            SearchResult searchResult;

            if (startPos == endPos) return searchResult;
            if (ContainsPosition(obstacles, endPos)) return searchResult;

            std::vector<SearchNode*> searchedNodes;
            std::vector<SearchNode*> searchingQueue;

            SearchNode* startNode = new SearchNode(startPos, 0, nullptr);
            searchedNodes.push_back(startNode);
            searchingQueue.push_back(startNode);

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

            bool success = false;

            while (!searchingQueue.empty())
            {
                SearchNode* currentNode = searchingQueue.front();
                searchingQueue.erase(searchingQueue.begin());

                int nextDepth = currentNode->depth + 1;
                //depth limit
                if (nextDepth > depthLimit)
                {
                    break;
                }

                for (size_t i = 0; i < searchDirection.size(); i++)
                {
                    Vector2 nextPosition = currentNode->position + searchDirection[i];

                    if (ContainsPosition(searchedNodes, nextPosition))
                    {
                        continue;
                    }
                    if (ContainsPosition(obstacles, nextPosition))
                    {
                        continue;
                    }

                    SearchNode* nextNode = new SearchNode(nextPosition, nextDepth, currentNode);
                    searchedNodes.push_back(nextNode);

                    if (nextPosition == endPos)
                    {
                        success = true;
                        break;
                    }

                    if (searchMethod == SearchMethod::BFS)
                    {
                        searchingQueue.push_back(nextNode);
                    }
                    else if (searchMethod == SearchMethod::DFS)
                    {
                        //Distance guidance
                        if (Vector2::Distance(nextPosition, endPos) <
                            Vector2::Distance(currentNode->position, endPos))
                        {
                            searchingQueue.insert(searchingQueue.begin(), nextNode);
                        }
                        else
                        {
                            searchingQueue.push_back(nextNode);
                        }
                    }
                }

                if (success)
                {
                    break;
                }
            }

            if (success)
            {
                searchResult.success = true;

                std::vector<SearchNode*> reversedPath;
                SearchNode* endNode = searchedNodes[searchedNodes.size() - 1];
                reversedPath.push_back(endNode);
                while (endNode->preNode != nullptr)
                {
                    endNode = endNode->preNode;
                    reversedPath.push_back(endNode);
                }

                //reverse
                for (int i = reversedPath.size() - 1; i >= 0; i--)
                {
                    searchResult.path.push_back(
                        Node(reversedPath[i]->position, reversedPath[i]->depth));
                }

                //add to searchResult and delete searchedNodes
                for (int i = 0; i < searchedNodes.size(); i++)
                {
                    searchResult.searchedNodes.push_back(
                        Node(searchedNodes[i]->position, searchedNodes[i]->depth));
                    delete searchedNodes[i];
                }
            }

            return searchResult;
        }
    };
}