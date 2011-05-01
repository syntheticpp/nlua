

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

    /* pil:
    size_t nbytes = sizeof(NumArray) + (n - 1)*sizeof(double);
    NumArray *a = (NumArray *)lua_newuserdata(L, nbytes);
    luaL_getmetatable(L, "LuaBook.array");
    lua_setmetatable(L, -2);
    */

    size_t num = (n - 1)*sizeof(double);
    NumArray* a = nlua::BoxedData<NumArray>::create(L, num, "LuaBook.array");
    
    a->size = n;
    return 1;  /* new userdatum is already on the stack */
}


static NumArray *checkarray (lua_State *L)
{
    //pil: void *ud = luaL_checkudata(L, 1, "LuaBook.array");
    NumArray* ud = nlua::BoxedData<NumArray>::address(L, 1);

    luaL_argcheck(L, ud != NULL, 1, "`array' expected");
    return ud;
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
    nlua::Engine m; 
    nlua::Global g(m); 
    
    nlua::Table<> a = g.tableAuto("array");
    a.setMetatable("LuaBook.array");
    a["new"] = newarray;
    a["set"] = setarray;
    a["get"] = getarray;
    a["size"] = getsize;

    bool error1 = m.doString(test_script_28_1);
    bool error2 = m.doString(test_script_28_2);

    return error1 && !error2 ? 0 : 1; // there should be an error
}



