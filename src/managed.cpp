/****************************************************************************
* Copyright (C) 2011 Peter Kümmel
* All rights reserved.
*
* This file is part of the nlua and licensed under the licenses enlisted
* in the file COPYING included in the packaging of this file.
****************************************************************************/
#include <nlua/managed.h>


namespace nlua
{

    //****************************************************************************
    //        class Managed
    //****************************************************************************

    Managed::Managed() :    ref(-1), isNil_(true)
    {
    }


    Managed::~Managed()
    {
    }


    Managed::Managed(const Managed& rhs) :    ref(-1), isNil_(true)
    {
        operator=(rhs);
    }


    Managed::Managed(lua_State* s) :    ref(-1), isNil_(true)
    {
        registry.init(s);    
    }


    bool Managed::isObject(const int index) const
    {
        return lua_istable(luaState(), index) || lua_isuserdata(luaState(), index);
    }


    void Managed::registerObject(const int index) 
    {
        lua_State*  s = luaState();
        // use table on stack position index as table
        if(!isObject(index)) 
            error("Managed::Managed(lua_State*): error, there is no table on top of the stack");

        registry.init(s);                                
        ref = registry.registerObject(index);     
        isNil_ = false;
    }


    void Managed::unregister()
    {
        if (ref != -1) {
            registry.unregisterObject(*this);    
            ref = -1;
        }
    }

    
    Managed& Managed::operator=(const Managed& rhs)
    { 
        if(&rhs != this)
        {
            ref = rhs.ref;
            isNil_ = rhs.isNil_; 
            registry = rhs.registry;
        }
        return *this; 
    }


    void Managed::push() const
    {                                                              // 
        registry.push();                                           // registry
        lua_rawgeti(luaState(), -1, ref);                          // registry thist
        if(!isObject(-1))
            error("Managed::push: error, no lua object available");
        lua_insert(luaState(), -2);                                // thist registry
        registry.pop();                                            // thist
    }


    void Managed::pop() const
    {    
        lua_State*  s = luaState();
                                               // table
        push();                                // table table
        if (lua_equal(s, -1, -2))    
            lua_pop(s, 2);                     // 
        else
        {
            lua_pop(s, 1);
            error("Managed::pop: error, cannot pop different value");
        }
    }


    bool Managed::isNil() const
    {
        return isNil_;
    }


    Managed::operator lua_State*() 
    {
        return luaState();
    }


    Managed::operator lua_State*() const
    {
        return luaState();
    }


    void Managed::setLuaState(lua_State* s) 
    {
        return registry.setLuaState(s);
    }


    lua_State* Managed::luaState() const
    {
        return registry.luaState();
    }


    void Managed::use()
    {
        registerObject(-1);
        pop();
    }


    void Managed::use(const int index)
    {
        registerObject(index);
    }


}

