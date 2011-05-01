/****************************************************************************
* Copyright (C) 2011 Peter Kümmel
* All rights reserved.
*
* This file is part of the nlua and licensed under the licenses enlisted
* in the file COPYING included in the packaging of this file.
****************************************************************************/
#include <nlua/object.h>

#include <nlua/metatable.h>



namespace nlua
{
    
    //****************************************************************************
    //        class Object
    //****************************************************************************

    Object::Object() :  Managed()
    {
    }


    Object::Object(const Object& rhs) :  Managed(rhs.luaState())
    {
        operator=(rhs);
    }


    Object::Object(lua_State* s) :  Managed(s)
    {        
    }


    Object::~Object()
    {
    }


    Object& Object::operator=(const Object& rhs)
    { 
        if(&rhs != this)
        {
            Managed::operator=(rhs);        
        }
        return *this; 
    }


    void Object::setValuesMetatable(const std::string& key, const std::string& mtname)
    {
        Metatable<> mt(*this, mtname);
        setValuesMetatable(key, mt);
    }


    void Object::setValuesMetatable(const std::string& key, const PlainTable& mt)
    {
        if(luaState() != mt.luaState())
            error("Object::add: error, differnt lua states");

        pushValue(key);                      // value
        mt.push();                           // value mt
        lua_setmetatable(luaState(), -2);    // value
        popValue(key);                       // 
    }


    void Object::setMetatable(const PlainTable& mt)
    {
        if(luaState() != mt.luaState())
            error("Object::add: error, differnt lua states");

        push();                              // thist
        mt.push();                           // thist mt
        lua_setmetatable(luaState(), -2);    // thist
        pop();                               // 
    }


    void Object::setMetatable(const std::string& name)
    {        
        Metatable<> mt(*this, name);
        setMetatable(mt);                    
        
        /*
                                              // 
        push();                               // thist
        if(!name.empty())
            luaL_newmetatable(*this, name.c_str());    
        else
            lua_newtable(*this);              // thist mt
        PlainTable mt(*this);                 // thist mt
        mt.use();                             // thist 
        pop();                                // 
        setMetatable(mt);                     // 
        */
    }


    PlainTable Object::metatable() const
    {                                                //
        push();                                      // thist
        if(lua_getmetatable(luaState(), -1))
        {
            PlainTable mt(luaState());               // thist mt
            mt.use();                                // this
            pop();                                   // 
            return mt;
        }
        else
        {                                            // thist
            pop();                                   // 
            return PlainTable();
        }
    }


    PlainTable Object::metatableAuto()
    {
        PlainTable mt =  metatable();
        if(!mt.isNil())    
        {
            return mt;
        }
        else
        {        
            // nameless table as metatable
            push();                             // thist
            lua_newtable(*this);                // thist mt
            PlainTable mt(*this);               // thist mt
            mt.use();                           // thist 
            pop();                              // 
            setMetatable(mt);
            return metatable();
        }
    }


    void Object::pushValue(const std::string& key) const
    {                                                   //
        push();                                         // thist    
        lua_pushstring    (luaState(), key.c_str());    // thist key
        lua_rawget        (luaState(), -2);             // thist value    
        if(lua_isnil(luaState(),-1)!=0)
            error(std::string("ERROR in PlainTable::pushvalue(const std::string& key) - no such value: ")+key);
        lua_insert(luaState(), -2);                     // value thist
        pop();                                          //
    }    


    void Object::popValue(const std::string& key) const
    {                                                   // value
        push();                                         // value thist    
        lua_pushstring    (luaState(), key.c_str());    // value thist key
        lua_rawget        (luaState(), -2);             // value thist value    

        if (lua_equal(luaState(), -1, -3))    
            lua_pop(luaState(), 3);                     // 
        else
        {
            lua_pop(luaState(), 3);                     //
            error("PlainTable::pop: error, cannot pop different value");
        }    
    }


}


