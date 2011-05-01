

#include "nluatest.h"

#include "numarray.h"



//
// http://www.lua.org/pil/28.4.html
//
// with a simpler array and fixes for Lua 5.2
//



static int newarray (lua_State *L)
{
    int n = luaL_checkint(L, 1);
    size_t nbytes = sizeof(NumArray) + (n - 1)*sizeof(double);
    NumArray *a = (NumArray *)lua_newuserdata(L, nbytes);
    
    luaL_getmetatable(L, "LuaBook.array");
    lua_setmetatable(L, -2);
    
    a->size = n;
    return 1;  /* new userdatum is already on the stack */
}


static NumArray *checkarray (lua_State *L)
{
    void *ud = luaL_checkudata(L, 1, "LuaBook.array");
    luaL_argcheck(L, ud != NULL, 1, "`array' expected");
    return (NumArray *)ud;
}


static int getsize (lua_State *L)
{
    NumArray *a = checkarray(L);
    lua_pushnumber(L, a->size);
    return 1;
}


static double *getelem (lua_State *L)
{
    NumArray *a = checkarray(L);
    int index = luaL_checkint(L, 2);
    
    luaL_argcheck(L, 1 <= index && index <= a->size, 2, "index out of range");
    
    /* return element address */
    return &a->values[index - 1];
}


static int setarray (lua_State *L)
{
    double newvalue = luaL_checknumber(L, 3);
    *getelem(L) = newvalue;
    return 0;
}


static int getarray (lua_State *L)
{
    lua_pushnumber(L, *getelem(L));
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

    luaL_newmetatable(L, "LuaBook.array");
    luaL_register(L, "array", arraylib);


    /* now the stack has the metatable at index 1 and
    `array' at index 2 */
    lua_pushstring(L, "__index");
    lua_pushstring(L, "get");
    lua_gettable(L, 2);  /* get array.get */
    lua_settable(L, 1);  /* metatable.__index = array.get */
    
    lua_pushstring(L, "__newindex");
    lua_pushstring(L, "set");
    lua_gettable(L, 2); /* get array.set */
    lua_settable(L, 1); /* metatable.__newindex = array.set */


    int error1 = 0;
    error1 = luaL_dostring(L, test_script_28_4);
    reportOnError(error1, L);

    lua_close(L);

    return (error1 == 0) ? 0 : 1;
}



