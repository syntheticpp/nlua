

#include "nluatest.h"

#include "numarray.h"


//
// Like 28.1 without lua_CFunctions but member functions  
//



class NumArrayHost : public NumArray
{
public:


    static int newarray (lua_State *L) 
    {
        int n = luaL_checkint(L, 1);

        //pil: size_t nbytes = sizeof(NumArray) + (n - 1)*sizeof(double);
        //pil: NumArray *a = (NumArray *)lua_newuserdata(L, nbytes);

        size_t num = (n - 1)*sizeof(double);               
        NumArray* a = nlua::BoxedData<NumArrayHost>::create(L, num);

        a->size = n;
        return 1;  /* new userdatum is already on the stack */
    }


    double getsize()
    {
        return size;
    }


    double getarray(int i)
    {
        if(i > 0 && i <= size) {
            return values[i - 1];
        } else {
            throw 333;
        }
    }


    void setarray(int i, double v)
    {
        if(i > 0 && i < size) {
            values[i - 1] = v;
        }
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