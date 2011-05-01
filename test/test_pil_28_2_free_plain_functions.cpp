

#include "nluatest.h"

#include "numarray.h"


//
// 28.2 without free lua_CFunctions 
//


// TODO!
int newarray (lua_State *L) 
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


double getsize(NumArray* a)
{
    return a->size;
}


double getarray(NumArray* a, int i)
{
    if(i<a->size && i>0) {
        return a->values[i-1];
    } else {
        return 0;
    }
}


void setarray(NumArray* a, int i, double v)
{
    if(i<a->size && i>0) {
        a->values[i-1] = v;
    }
}



int main()
{
    nlua::Engine m; 
    nlua::Global g(m); 
    
    nlua::Table<NumArray> a = g.tableAuto("array");
    a.setMetatable("LuaBook.array");
    a["new"] = newarray;
    a["set"] = setarray;
    a["get"] = getarray;
    a["size"] = getsize;

    bool error1 = m.doString(test_script_28_1);
    bool error2 = m.doString(test_script_28_2);

    return error1 && !error2 ? 0 : 1; // there should be an error
}

