#include "Header.h"
using namespace std;

EXTERN_C int write(lua_State* L)
{
    // Get First argument from lua
    const char* param1 = lua_tostring(L, 1);
    //null check
    if (param1 == nullptr)
    {
        //do nothing.
    }
    else
    {
        //here must set Encoding to UTF8
        wstring wstr = String::StringToWstring(string(param1), Encoding::UTF8);
        //output
        console.Write(wstr);
    }

    return 0; // no return value
}

EXTERN_C int writeline(lua_State* L)
{
    // Get First argument from lua
    const char* param1 = lua_tostring(L, 1);
    //null check
    if (param1 == nullptr)
    {
        console.WriteLine();
    }
    else
    {
        //here must set Encoding to UTF8
        wstring wstr = String::StringToWstring(string(param1), Encoding::UTF8);
        //output
        console.WriteLine(wstr);
    }

    return 0; // no return value
}

EXTERN_C int readkey(lua_State* L)
{
    //readkey
    wchar c = console.ReadKey().KeyChar;
    //wchar -> wstring
    wstring wstr = String::WcharToWstring(c);
    //here must set Encoding to UTF8
    string str = String::WstringToString(wstr, Encoding::UTF8);

    //return to lua as return value
    lua_pushstring(L, str.c_str());

    return 1; // one return value
}

EXTERN_C int getkey(lua_State* L)
{
    // Get First argument from lua
    int param1 = lua_tointeger(L, 1);
    //detect key input
    bool get = Input::GetKey(param1);

    //return to lua as return value
    lua_pushinteger(L, get);

    return 1; // one return value
}

EXTERN_C int sleep(lua_State* L)
{
    // Get First argument from lua
    int param1 = lua_tointeger(L, 1);
    //sleep
    ::Sleep(param1);

    return 0; // no return value
}

void LuaRegisteInt(lua_State* L, const char* key, int value)
{
    //push var to lua state:
    lua_pushinteger(L, value);
    lua_setglobal(L, key);
}

int main()
{
    //combine lua folder path
    wstring dirPath = File::GetDirectoryPath();
    wstring luaScriptsFolder = File::Combine(dirPath, L"scripts");

    //get config
    Database data(L"config.txt");
    wstring luaFileName = data.GetString(L"LuaFileName", L"null");
    if (luaFileName == L"null")
    {
        console.WriteLine(L"lua file cannot find!");
        console.ReadKey();
        return 0;
    }
    //combine lua path
    wstring luaFilePath = File::Combine(luaScriptsFolder, luaFileName);

    //--------------- start Lua VM ---------------
    //new
    lua_State* L = luaL_newstate();
    //enable print method and so on
    luaL_openlibs(L);

    //registe vars:
    LuaRegisteInt(L, "BLAST_ENGINE", 1);

    //registe functions:
    lua_register(L, "readkey", readkey);
    lua_register(L, "write", write);
    lua_register(L, "writeline", writeline);
    lua_register(L, "getkey", getkey);
    lua_register(L, "sleep", sleep);

    //do luaFile: 0=correct, 1=error
    bool _exe_suc = !luaL_dofile(L, String::WstringToString(luaFilePath).c_str());

    if (_exe_suc)
    {
        console.WriteLine(L"执行成功");
    }
    else
    {
        console.WriteLine(L"执行失败");
    }

    //delete
    lua_close(L);

    console.ReadKey();
    return 0;
}