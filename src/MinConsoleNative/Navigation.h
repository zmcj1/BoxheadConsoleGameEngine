#pragma once

#include "MinDefines.h"
#include "Vector2.h"
#include <vector>

namespace MinConsoleNative
{
#define NAV_UNLIMITED_DEPTH (-1)

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

        static bool ContainsPosition(const std::vector<Node>& container, const Vector2& element)
        {
            for (int i = 0; i < container.size(); i++)
            {
                if (container[i].position == element) return true;
            }
            return false;
        }

        //if depthLimit == NAV_UNLIMITED_DEPTH means the program won't get stop because of depth.
        static SearchResult Navigate(Vector2 startPos, Vector2 endPos, SearchDirection searchDir, int depthLimit, const std::vector<Vector2>& obstacles, SearchMethod searchMethod);
    };
}