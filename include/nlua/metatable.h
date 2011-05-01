/****************************************************************************
* Copyright (C) 2011 Peter Kümmel
* All rights reserved.
*
* This file is part of the nlua and licensed under the licenses enlisted
* in the file COPYING included in the packaging of this file.
****************************************************************************/
#ifndef NLUA_METATABLE_H
#define NLUA_METATABLE_H

#include <nlua/table.h>
#include <nlua/engine.h>
#include <nlua/global.h>

#include <string>


namespace  nlua
{

    //****************************************************************************
    //        class Metatable
    //****************************************************************************

    template<class Host = void>
    class Metatable : public Table<Host>
    {
    public:
        Metatable(lua_State*, const std::string &);
        virtual ~Metatable();

        Metatable(const Metatable&);

        static bool exists(lua_State*, const std::string&);

        std::string name();
        void pushName();

    private:
        Metatable();
        Metatable& operator=(const Metatable&);
        const std::string name_;
    };



    //****************************************************************************
    //         Metatable definition
    //****************************************************************************

    template<class Host>
    Metatable<Host>::Metatable(lua_State* s, const std::string& mtname) : Managed(s), Table<Host>(), name_(mtname)
    {
        if(mtname.empty()) {
            error("Metatable::Metatable: error, no valid name");
        }
        luaL_newmetatable(s, mtname.c_str());    
        PlainTable::use();
    }


    template<class Host>
    Metatable<Host>::~Metatable()
    {
    }


    template<class Host>
    Metatable<Host>::Metatable(const Metatable& rhs) : Table<Host>(), name_(rhs.name_)
    {
        PlainTable::operator=(rhs);
    }


    template<class Host>
    bool Metatable<Host>::exists(lua_State* L, const std::string& mtname)
    {
        luaL_getmetatable(L, mtname.c_str());
        bool b = !lua_isnil(L, -1);
        lua_pop(L, 1);
        return b;
    }


    template<class Host>
    void Metatable<Host>::pushName()
    {
        lua_pushstring(*this, name_.c_str());
    }


    //****************************************************************************
    //         global push
    //****************************************************************************

    template<class Host>
    struct push<Metatable<Host> >
    {
        static inline void value(lua_State* L, const Metatable<Host>& table)
        {
            if( L!=table.luaState()) {
                error("void pushValue(lua_State*,const Object&): different lua states");
            }
            table.push();
        }
    };

}

#endif
