#pragma once

#include "MinDefines.h"
#include <vector>

namespace MinConsoleNative
{
    template<typename Object>
    class ObjectPool
    {
    public:
        std::vector<Object*> pool;

    public:
        ObjectPool(int count)
        {
            PreAllocate(count);
        }

        ~ObjectPool()
        {
            for (size_t i = 0; i < pool.size(); i++)
            {
                delete pool[i];
            }
        }

        void PreAllocate(int count)
        {
            for (int i = 0; i < count; i++)
            {
                Object* instance = new Object();
                ReturnInstance(instance);
            }
        }

        Object* GetInstance()
        {
            if (!pool.empty())
            {
                Object* instance = pool.back();
                pool.pop_back();
                return instance;
            }
            return new Object();
        }

        void ReturnInstance(Object* instance)
        {
            pool.push_back(instance);
        }
    };
}