/****************************************************************************
* Copyright (C) 2011 Peter Kümmel
* All rights reserved.
*
* This file is part of the nlua and licensed under the licenses enlisted
* in the file COPYING included in the packaging of this file.
****************************************************************************/
#include <nlua/plaintable.h>
#include <nlua/metatable.h>


namespace nlua
{
    
    //****************************************************************************
    //        class PlainTable
    //****************************************************************************

    PlainTable::PlainTable() :  Managed()
    {
    }


    PlainTable::PlainTable(const PlainTable& rhs) :  Managed()
    {
        operator=(rhs);
    }


    PlainTable::PlainTable(lua_State* s) :  Managed(s)
    {        
    }


    void PlainTable::create() 
    {                                    //
        lua_newtable(luaState());        // table
        use();                           //
    }


    PlainTable::~PlainTable()
    {
    }


    PlainTable& PlainTable::operator=(const PlainTable& rhs)
    { 
        if(&rhs != this)
        {
            Managed::operator=(rhs);        
        }
        return *this; 
    }


    PlainTable PlainTable::table(const int index) const
    {                                            
        lua_pushvalue    (luaState(), index);    // key 
        push();                                  // key thist
        lua_pushvalue    (luaState(), -2);       // key thist key
        lua_rawget        (luaState(), -2);       // key thist t    

        if(lua_istable    (luaState(), -1))
        {                               // key thist t    
            PlainTable t(luaState());    // key thist t    
            t.use();         // key thist 
            pop();                      // key
            lua_pop(luaState(), 1);     // 
            return t;
        }
        else
        {
                                       // key thist ?    
            lua_pop(luaState(), 1);    // key thist
            pop();                     // key
            lua_pop(luaState(), 1);    // 
            return PlainTable();        // return not initialized table;
        }
    }    


    PlainTable PlainTable::table(const std::string& key) const
    {                                            
                                                        // 
        lua_pushstring    (luaState(), key.c_str());    // key
        PlainTable t = table    (-1);                    // key 
        lua_pop            (luaState(), 1);             // 
        return t;
    }


    PlainTable PlainTable::tableAuto(const std::string& key) 
    {
        PlainTable t = table(key);
        if(!t.isNil())
        {
            return t;
        }
        else
        {
            PlainTable newt(luaState());
            newt.create();
            setValue(key, newt);
            return newt;
        }
    }


    void PlainTable::setClosure(const std::string& key, lua_CFunction f, int upvalues)
    {
        if (key.empty())
            error("settable: error, key is empty");

        lua_State* L = luaState();

        for(int i=1; i<=upvalues; i++)
            if(lua_isnil(L,-i))
                error("setClosure: no valid upvalues");;
        
        // table[key] = value:                     // upvalues
        lua_pushcclosure    (L, f, upvalues);      // cclosure
        push();                                    // cclosure t
        lua_pushstring        (L, key.c_str());    // cclosure t key
        lua_pushvalue       (L, -3);               // cclosure t key cclosure
        lua_rawset            (L, -3);             // cclosure t
        pop();                                     // cclosure
        lua_pop             (L,1);                 //
    }

}


