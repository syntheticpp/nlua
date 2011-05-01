

#include "nluatest.h"

#include "double.h"



 // TODO
template<class T>
int create(lua_State* L)
{        
    T* t = nlua::Userdata<T>(L).create();
    return 1; 
}



int main()
{

    nlua::Engine m; 
    nlua::Global g(m); 
    
    nlua::Userdata<Double> u(m);
    u.create();

    u.data()->set(1);

    g.setValue("d", u);
    
    nlua::Table<Double> meta = u.metatable();

    meta["__index"] = meta;
    meta["set"] = &Double::set;
    meta["get"] = &Double::get;
    meta["__gc"] = u.destructor();
  
    
    bool error1 = m.doString(

        "function set(t,name,value) \n"
        "    print(\"set\",name,value) \n"
        "end \n"

        "function get(t,name) \n"
        "    print(\"get\",name) \n"
        "    return name \n"
        "end \n"
        
        "--mt = getmetatable(d)  \n"
        "--mt.__index = get \n"
        "--mt.__newindex = mt.set \n"

        "print(d:get()); \n"
        "d:set(2.2); \n"
        "print(d:get()); \n"
        );
        
    double d = u.data()->get();

    return error1 && d == 2.2 ? 0 : 1;
}

