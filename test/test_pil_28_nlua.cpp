

#include "nluatest.h"

#include "numarray.h"


//
// Like 28.4 the nlua way
//





class NumArrayHost : public NumArray
{
public:


    double getsize()
    {
        return size;
    }


    double* getelem (int index)
    {
        if(index > 0 && index <= size) {
            return &values[index - 1];
        } else {
            // Lua compiled as C++ ctaches exceptions
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


// TODO
static int newarray (lua_State *L)
{
    int n = luaL_checkint(L, 1);

    size_t num = (n - 1)*sizeof(double);
    NumArray* a = nlua::BoxedData<NumArrayHost>::create(L, num);
    
    a->size = n;
    return 1;  /* new userdatum is already on the stack */
}



int main()
{
    nlua::Engine m; 
    nlua::Global g(m); 
    
    nlua::Userdata<NumArrayHost> u1(m);
    int size = 1000;
    u1.create(size);
    u1.data()->size = size;

    nlua::Table<NumArrayHost> meta = u1.metatable();
    meta["__newindex"] = &NumArrayHost::setarray;
    meta["__index"] = &NumArrayHost::getarray;


    nlua::Userdata<NumArrayHost> u2(m);
    NumArrayHost n;
    n.setarray(1, 111);
    u2.setData(&n);
    u2.setMetatable(meta);


    nlua::Table<> t3(m);
    t3.create();
    t3["new"] = &newarray;


    g["a1"] = u1;
    g["a1"] = u1;
    g["a2"] = u2;
    g["t3"] = t3;

    bool error = m.doString(

        "a1[10] = 11                    \n"
        "print(a1[10])                 \n"

        "print(a2[1])                  \n"
        "a2[1] = 222                    \n"
        "print(a2[1])                  \n"

        "a3 = t3.new(1000)             \n"
        "a3[10] = 3333                  \n"
        "print(a3[10])                 \n"

        );

    return error 
            && u1.data()->getarray(10) == 11
            && u2.data()->getarray(1) == 222
            && n.getarray(1) == 222
            && u2.data() == &n
            ? 0 : 1;
}
