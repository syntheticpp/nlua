/****************************************************************************
* Copyright (C) 2011 Peter Kümmel
* All rights reserved.
*
* This file is part of the nlua and licensed under the licenses enlisted
* in the file COPYING included in the packaging of this file.
****************************************************************************/
#include <nlua/objectregistry.h>
#include <nlua/managed.h>

#include <iostream>

//#define NLUA_OBJECTREGISTRY_DEBUG

namespace nlua
{

    const char * obj_registry = "NLUA_REGISTRY_FOR_ALL_TABLES";
    

    ObjectRegistry::ObjectRegistry() : state(0), luareference(0)
    {
    }
    

    ObjectRegistry::~ObjectRegistry()
    {
    }


    ObjectRegistry& ObjectRegistry::operator=(const ObjectRegistry& rhs)
    {
        state = rhs.state;
        luareference = rhs.luareference;
        return *this;
    }


    void ObjectRegistry::setLuaState(lua_State* s) 
    {
        state = s;
        s = luaState(); // check
    }


    lua_State* ObjectRegistry::luaState() const
    {
        if(state==0)
            error("Object::luaState() no valid lua_State.");
        return state;
    }


    void ObjectRegistry::init(lua_State* s)
    {    
        // additional registry table to manage table identities: 
        //
        //        reg[i]        = table
        //        reg[table]    = i
        //
        // all non nil tables have a non NULL lua_State
        // and a entry in the additional registry
        //
        // because there can be reg[table] = std::string fields
        // in the registry table at LUA_REGISTRYINDEX 
                                                
        state = s;
        s = luaState(); //check
                                                                // 
        lua_pushstring    (s, obj_registry);                    // name
        lua_rawget        (s, LUA_REGISTRYINDEX);               // registry 

        if(!lua_istable(luaState(), -1))                        // allready exists?            
        {        
            //LUA_REGISTRYINDEX[i] = nlua_registy:          // nil
            lua_pop           (s, 1);                       //
            lua_newtable      (s);                          // t
            lua_pushvalue     (s, -1);                      // t t
            lua_pushstring    (s, obj_registry);            // t t key
            lua_pushvalue     (s, -2);                      // t t key t
            lua_rawset        (s, LUA_REGISTRYINDEX);       // t    LUA_REGISTRYINDEX[ std::string& ]    = obj_registry    
            luareference=luaL_ref(s, LUA_REGISTRYINDEX);    // t    LUA_REGISTRYINDEX[ number ]    = table    

            
            lua_pushnumber    (s, static_cast<lua_Number>(luareference));    
                                                            // t number
            lua_rawset        (s, LUA_REGISTRYINDEX);       //        LUA_REGISTRYINDEX[ table ]    = number
        }
        else
        {                                                   // registry
            lua_rawget(s, LUA_REGISTRYINDEX);               // int
            if(lua_isnumber(s,-1))
            {
                luareference = static_cast<int>(lua_tonumber(s,-1));
                lua_pop(s, 1);                              // 
            }
            else
            {
                error("ObjectRegistry::initregistryref: error, there is a registry chaos");
            }
        }
    }


    int ObjectRegistry::registerObject(int index)
    {
        // add thist to registry
        int ref = -1;
        lua_State*  s = luaState();

        if( !(lua_istable(s, index) || lua_isuserdata(s, index)) )
            error("ObjectRegistry::registertable: error, there is no table or userdata on top of the stack");
                                    
                                       //
        lua_pushvalue   (s, index);    // table
        push();                        // table registry
        lua_pushvalue   (s, -2);       // table registry table
        lua_rawget      (s, -2);       // table registry ref
        // check if already registered
        if(lua_isnumber(s, -1))
        {
            ref = static_cast<int>(lua_tonumber(s,-1));
            lua_pop(s, 1);             // table registry
#ifdef NLUA_OBJECTREGISTRY_DEBUG
            std::cout << "Object allready registered with key: " << ref <<"\n";
#endif
        }
        else
        {                                 // table registry ?
            lua_pop           (s, 1);     // table registry
            lua_pushvalue     (s, -2);    // table registry table
            ref = luaL_ref    (s, -2);    // table registry    

            // now registry[ ref ] = table    
#ifdef NLUA_OBJECTREGISTRY_DEBUG
            std::cout << "Object registered with key: " << ref <<"\n";
#endif
            lua_pushvalue     (s, -2);                              // table registry table
            lua_pushnumber    (s, static_cast<lua_Number>(ref));    // table registry table ref
            lua_rawset        (s, -3);                              // table registry

            // now registry[ table ] = ref
        }
        pop();                                    // table
        lua_pop(s, 1);                            //

        return ref;
    }


    void ObjectRegistry::unregisterObject(const Managed& t)
    {
        lua_State*  s = luaState();
        t.push();                     // t
        push();                       // t registry
        lua_pushvalue     (s, -2);    // t registry t
        lua_rawget        (s, -2);    // t registry ref
        if(!lua_isnumber(s, -1))
        {    // not registered
            lua_pop(s, 1);            // t registry
        }
        else
        {
            int i = static_cast<int>(lua_tonumber(s,-1));
                                             // t registry ref
            lua_pop      (s, 1);        // t registry 
            luaL_unref   (s, -1, i);    // t registry            // registry[ ref ] is now free
            lua_pushvalue(s, -2);       // t registry t
            lua_pushnil  (s);           // t registry t nil 
            lua_rawset   (s, -3);       // t registry            // registry[ thist ] = nil
#ifdef NLUA_OBJECTREGISTRY_DEBUG
            std::cout << "Object unregistered with key: " << i <<"\n";
#endif
        }
        pop();                            // t
        lua_pop(s, 1);                    //
        //t.pop();
    }


    void ObjectRegistry::push() const
    {
        lua_State*  s = luaState();
        lua_rawgeti(s, LUA_REGISTRYINDEX, luareference);      // registry 
        if(!lua_istable(s, -1))
            error("ObjectRegistry::pushRegistry: error, registry is not available");
    }


    void ObjectRegistry::pop() const
    {
        lua_State*  s = luaState();
        push();
        if (lua_equal(s, -1, -2))
            lua_pop(s, 2);
        else
        {
            lua_pop(s, 1);
            error("ObjectRegistry::popRegistry: error, cannot pop different value");
        }
    }

}

