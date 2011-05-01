

#include "nluatest.h"

#include "numarray.h"



//
// http://www.lua.org/pil/28.1.html
//
// with a simpler array and fixes for Lua 5.2
//


static int newarray (lua_State *L)
{
    int n = luaL_checkint(L, 1);
    size_t nbytes = sizeof(NumArray) + (n - 1)*sizeof(double);
    NumArray *a = (NumArray *)lua_newuserdata(L, nbytes);
    a->size = n;
    return 1;  /* new userdatum is already on the stack */
}


static int setarray (lua_State *L)
{
    NumArray *a = (NumArray *)lua_touserdata(L, 1);
    int index = luaL_checkint(L, 2);
    double value = luaL_checknumber(L, 3);

    luaL_argcheck(L, a != NULL, 1, "`array' expected");
    luaL_argcheck(L, 1 <= index && index <= a->size, 2, "index out of range");

    a->values[index-1] = value;
    return 0;
}


static int getarray (lua_State *L)
{
    NumArray *a = (NumArray *)lua_touserdata(L, 1);
    int index = luaL_checkint(L, 2);

    luaL_argcheck(L, a != NULL, 1, "`array' expected");
    luaL_argcheck(L, 1 <= index && index <= a->size, 2, "index out of range");

    lua_pushnumber(L, a->values[index-1]);
    return 1;
}


static int getsize (lua_State *L)
{
    NumArray *a = (NumArray *)lua_touserdata(L, 1);
    luaL_argcheck(L, a != NULL, 1, "`array' expected");
    lua_pushnumber(L, a->size);
    return 1;
}



int main()
{
    lua_State* L = lua_open();
    luaL_openlibs(L);

    const struct luaL_reg arraylib [] = {
        {"new", newarray},
        {"set", setarray},
        {"get", getarray},
        {"size", getsize},
        {NULL, NULL}};
    luaL_register(L, "array", arraylib);

    int error = luaL_dostring(L, test_script_28_1);

    lua_close(L);

    return error;
}



