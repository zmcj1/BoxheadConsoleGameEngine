#include "Navigation.h"
#include "Vector.h"

namespace MinConsoleNative
{
    SearchResult Navigation::Navigate(Vector2 startPos, Vector2 endPos, SearchDirection searchDir, int depthLimit, const std::vector<Vector2>& obstacles, SearchMethod searchMethod)
    {
        SearchResult searchResult;

        if (startPos == endPos) return searchResult;
        if (Vector<Vector2>::Contains(obstacles, endPos)) return searchResult;

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
            if (depthLimit != NAV_UNLIMITED_DEPTH && nextDepth > depthLimit)
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
                if (Vector<Vector2>::Contains(obstacles, nextPosition))
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
}