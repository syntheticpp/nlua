

#include "nluatest.h"

#include "double.h"



int main()
{
    nlua::Engine m; 
     
    Double d = 1;

    nlua::Userdata<Double> u(m);
    u.setData(&d);
    
    nlua::Table<Double> meta = u.metatable();
    
    meta["set"] = &Double::set;
    meta["get"] = &Double::get;
    meta["__index"] = meta;  
    
    nlua::Global g(m);
    g["d"] = u;

    bool error1 = m.doString(
        "print(d:get()); \n"
        "d:set(2.2); \n"
        "print(d:get()); \n"
        );
        

    return error1 && d.get() == 2.2 ? 0 : 1;
}

