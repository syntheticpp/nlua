

#include "nluatest.h"

#include "numarray.h"



//
// http://www.lua.org/pil/28.2.html
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

    int error1 = 0;
    error1 = luaL_dostring(L, test_script_28_1);
    reportOnError(error1, L);

    int error2 = luaL_dostring(L, test_script_28_2);
    reportOnError(error2, L);

    lua_close(L);

    return (error1 == 0 && error2 == 1) ? 0 : 1; // there should be an error
}



