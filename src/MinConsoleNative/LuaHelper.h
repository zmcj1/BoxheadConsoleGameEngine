#pragma once

#include "MinDefines.h"

extern "C"
{
#include "../../third_party/Lua542/include/lua.h"
#include "../../third_party/Lua542/include/lualib.h"
#include "../../third_party/Lua542/include/lauxlib.h"
}

namespace MinConsoleNative
{
    void lua_test();
}