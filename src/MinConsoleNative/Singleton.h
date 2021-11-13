#pragma once

#include "MinDefines.h"
#include <memory>

namespace MinConsoleNative
{
    template<typename T>
    class Singleton
    {
    private:
        Singleton()
        {
        }

    public:
        template<typename...Args>
        static T& GetInstance(Args&&...args)
        {
            static std::shared_ptr<T> instance =
                std::make_shared<T>(std::forward<Args>(args)...);
            return *(instance.get());
        }
    };
}