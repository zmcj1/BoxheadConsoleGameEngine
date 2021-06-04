#include "LuaHelper.h"
#include "Console.h"
#include <string>

#ifdef _WIN32 || WIN32
#pragma comment(lib, "../../third_party/Lua542/lua54.lib")
#endif

using namespace std;

namespace MinConsoleNative
{
    void lua_test()
    {
        lua_State* L = luaL_newstate();

        char cmd[32] = "a = 1 + 2";

        int r = luaL_dostring(L, cmd);

        if (r == LUA_OK)
        {
            lua_getglobal(L, "a");
            if (lua_isnumber(L, -1))
            {
                int a_in_cpp = (int)lua_tonumber(L, -1);
                console.WriteLine(L"a in cpp is:" + to_wstring(a_in_cpp));
            }
        }

        lua_close(L);
    }
}