

#include "nluatest.h"

#include "numarray.h"


//
// Like 28.3 without lua_CFunctions but plain member functions  
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


    double getsize()
    {
        return size;
    }


    double* getelem (int index)
    {
        if(index > 0 && index <= size) {
            return &values[index - 1];
        } else {
            // Lua compiled as C++ catches exceptions
            // TODO pass error message to Lua
            throw 333;
        }
        return 0;
    }


    void setarray(int i, double v)
    {
        if(getelem(i)) {
            *getelem(i) = v;
        }
    }


    double getarray(int i)
    {
        if(getelem(i)) {
            return *getelem(i);
        }
        return 0;
    }


};




int main()
{
    nlua::Engine m; 
    nlua::Global g(m); 
    

    nlua::Table<> a = g.tableAuto("array");
    a["new"] = &NumArrayHost::newarray;
    
    a.setMetatable("LuaBook.array");
    nlua::Table<NumArrayHost> meta = a.metatable();
    meta["set"] = &NumArrayHost::setarray;
    meta["get"] = &NumArrayHost::getarray;
    meta["size"] = &NumArrayHost::getsize;
    meta["__index"] = meta;
    
    bool error = m.doString(test_script_28_3);

    return  error ? 0 : 1;
}

