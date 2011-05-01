

#include "nluatest.h"

#include "numarray.h"



//
// Like 28.3  lua_CFunctions member functions  
//



class NumArrayHost : public NumArray
{
public:

    // TODO
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
        NumArray* a = nlua::BoxedData<NumArrayHost>::create(L, num, "LuaBook.array");
    
        a->size = n;
        return 1;  /* new userdatum is already on the stack */
    }


     void checkarray (lua_State *L)
    {
        //pil: void *ud = luaL_checkudata(L, 1, "LuaBook.array");
        NumArrayHost* ud = nlua::BoxedData<NumArrayHost>::address(L, 1);
        luaL_argcheck(L, ud != NULL, 1, "`array' expected");
    }


    int getsize (lua_State *L)
    {
        checkarray(L);
        lua_pushnumber(L, size);
        return 1;
    }


    double *getelem (lua_State *L)
    {
        checkarray(L);
        int index = luaL_checkint(L, 2);
    
        luaL_argcheck(L, 1 <= index && index <= size, 2, "index out of range");
    
        /* return element address */
        return &values[index - 1];
    }


    int setarray (lua_State *L)
    {
        double newvalue = luaL_checknumber(L, 3);
        *getelem(L) = newvalue;
        return 0;
    }


    int getarray (lua_State *L)
    {
        lua_pushnumber(L, *getelem(L));
        return 1;
    }


};





int main()
{
    nlua::Engine m; 
    nlua::Global g(m); 
    

    nlua::Table<NumArrayHost> a = g.tableAuto("array");
    a["new"] = &NumArrayHost::newarray;
    
    a.setMetatable("LuaBook.array");
    nlua::Table<NumArrayHost> meta = a.metatable();
    meta["set"] = &NumArrayHost::setarray;
    meta["get"] = &NumArrayHost::getarray;
    meta["size"] = &NumArrayHost::getsize;
    meta["__index"] = meta;
    
    bool error = m.doString(test_script_28_3);

    return error ? 0 : 1;
}


