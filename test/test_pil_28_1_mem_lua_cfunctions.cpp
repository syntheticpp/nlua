

#include "nluatest.h"

#include "numarray.h"


//
// Like 28.1  lua_CFunctions member functions  
//



class NumArrayHost : public NumArray
{
public:


    static int newarray (lua_State *L) 
    {
        int n = luaL_checkint(L, 1);

        size_t num = (n - 1)*sizeof(double);                         //pil: size_t nbytes = sizeof(NumArray) + (n - 1)*sizeof(double);
        NumArray* a = nlua::BoxedData<NumArrayHost>::create(L, num); //pil: NumArray *a = (NumArray *)lua_newuserdata(L, nbytes);

        a->size = n;
        return 1;  /* new userdatum is already on the stack */
    }


    int setarray (lua_State *L) 
    {
        luaL_argcheck(L, nlua::BoxedData<NumArrayHost>::address(L, 1) == this, 1, "`array' expected");

        int index = luaL_checkint(L, 2);
        double value = luaL_checknumber(L, 3);

        luaL_argcheck(L, 1 <= index && index <= size, 2,"index out of range");

        values[index-1] = value;
        return 0;
    }


    int getarray (lua_State *L) 
    {
        luaL_argcheck(L, nlua::BoxedData<NumArrayHost>::address(L, 1) == this, 1, "`array' expected");

        int index = luaL_checkint(L, 2);

        luaL_argcheck(L, 1 <= index && index <= size, 2,"index out of range");

        lua_pushnumber(L, values[index-1]);
        return 1;
    }


    int getsize (lua_State *L) 
    {
        luaL_argcheck(L, nlua::BoxedData<NumArrayHost>::address(L, 1) == this, 1, "`array' expected");

        lua_pushnumber(L, size);
        return 1;
    }

};




int main()
{
    nlua::Engine m; 
    nlua::Global g(m); 
    
    nlua::Table<NumArrayHost> a = g.tableAuto("array");

    a.setFunction("new", &NumArrayHost::newarray);
    a.setMemberFunction("set", &NumArrayHost::setarray);
    a.setMemberFunction("get", &NumArrayHost::getarray);
    a.setMemberFunction("size", &NumArrayHost::getsize);

    // or
    a["new"] = &NumArrayHost::newarray;
    a["set"] = &NumArrayHost::setarray;
    a["get"] = &NumArrayHost::getarray;
    a["size"] = &NumArrayHost::getsize;
    

    return m.doString(test_script_28_1) ? 0 : 1;
}