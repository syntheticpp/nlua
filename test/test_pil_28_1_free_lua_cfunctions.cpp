

#include "nluatest.h"

#include "numarray.h"





//
// Like 28.1 with free nlua_CFunctions but done with nlua
// 


int newarray (lua_State *L) 
{
    int n = luaL_checkint(L, 1);

    size_t num = (n - 1)*sizeof(double);                     //pil: size_t nbytes = sizeof(NumArray) + (n - 1)*sizeof(double);
    NumArray* a = nlua::BoxedData<NumArray>::create(L, num); //pil: NumArray *a = (NumArray *)lua_newuserdata(L, nbytes);

    a->size = n;
    return 1;  /* new userdatum is already on the stack */
}


int setarray (lua_State *L) 
{
    NumArray* a = nlua::BoxedData<NumArray>::address(L, 1); //pil: NumArray *a = (NumArray *)lua_touserdata(L, 1);
    int index = luaL_checkint(L, 2);
    double value = luaL_checknumber(L, 3);

    luaL_argcheck(L, a != NULL, 1, "`array' expected");
    luaL_argcheck(L, 1 <= index && index <= a->size, 2,"index out of range");

    a->values[index-1] = value;
    return 0;
}


int getarray (lua_State *L) 
{
    NumArray* a = nlua::BoxedData<NumArray>::address(L, 1); //pil: NumArray *a = (NumArray *)lua_touserdata(L, 1);
    int index = luaL_checkint(L, 2);

    luaL_argcheck(L, a != NULL, 1, "`array' expected");
    luaL_argcheck(L, 1 <= index && index <= a->size, 2,"index out of range");

    lua_pushnumber(L, a->values[index-1]);
    return 1;
}


int getsize (lua_State *L) 
{
    NumArray* a = nlua::BoxedData<NumArray>::address(L, 1); //pil: NumArray *a = (NumArray *)lua_touserdata(L, 1);

    luaL_argcheck(L, a != NULL, 1, "`array' expected");
    lua_pushnumber(L, a->size);
    return 1;
}


int main()
{
    nlua::Engine m; 
    nlua::Global g(m); 
    
    nlua::Table<NumArray> a = g.tableAuto("array");
    a["new"] = newarray;
    a["set"] = setarray;
    a["get"] = getarray;
    a["size"] = getsize;

    return m.doString(test_script_28_1) ? 0 : 1;
}



