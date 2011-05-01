

#include "nluatest.h"

#include "numarray.h"

#include <nlua/userdata.h>

//
// 28.1 without free lua_CFunctions 
//


// TODO!
int newarray (lua_State *L) 
{
    int n = luaL_checkint(L, 1);

    size_t num = (n - 1)*sizeof(double);                     //pil: size_t nbytes = sizeof(NumArray) + (n - 1)*sizeof(double);
    NumArray* a = nlua::BoxedData<NumArray>::create(L, num); //pil: NumArray *a = (NumArray *)lua_newuserdata(L, nbytes);

    a->size = n;
    return 1;  /* new userdatum is already on the stack */
}


double getsize(NumArray* a)
{
    return a->size;
}


double getarray(NumArray* a, int i)
{
    //cout << "called: getarrayC("<<a<<"): " << a->values[i-1] << " returned \n";
    if(i<a->size && i>0) {
        return a->values[i-1];
    } else {
        return 0;
    }
}


void setarray(NumArray* a, int i, double v)
{
    //cout << "called: setarrayC("<<a<<", "<<i<<", " << v << ")\n";
    if(i<a->size && i>0) {
        a->values[i-1] = v;
    }
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