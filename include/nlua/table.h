/****************************************************************************
* Copyright (C) 2011 Peter Kümmel
* All rights reserved.
*
* This file is part of the nlua and licensed under the licenses enlisted
* in the file COPYING included in the packaging of this file.
****************************************************************************/
#ifndef NLUA_TABLE_H
#define NLUA_TABLE_H

#include <nlua/object.h>
#include <nlua/plaintable.h>
#include <nlua/userdata.h>
#include <nlua/typename.h>

#ifndef _MSC_VER
#include <tr1/type_traits>
#else
#include <type_traits>
#endif


namespace  nlua
{

    namespace details
    {
        template<class Table, bool IsMemberFunction>
        struct SetFreeOrMember;
    }


    //****************************************************************************
    //        class Table
    //****************************************************************************

    template<class Host = void>
    class Table;


    template<class Host>
    class Table : public Object, public PlainTable
    {
    public:

        Table(); 
        virtual ~Table();
        
        explicit Table(lua_State*);
        Table(const PlainTable&);

        template<typename Func>
        void setMemberFunction(const std::string& key, const Func func);

        struct LhsReference
        {
            LhsReference(const std::string& k, Table* t);

            template<typename Func>
            Table& operator=(const Func func);
            Table& operator=(const Table& t);

        private:
            const std::string& key;
            Table* table;
        };

        LhsReference operator[](const std::string& key) { return LhsReference(key, this); }
       
    };



    namespace details
    {
       
        template<class Table>
        struct SetFreeOrMember<Table, true>
        {
            template<typename Func>
            static
            void function(Table* table, const std::string& key, const Func func)
            {
                table->setMemberFunction(key, func);
            }
        };
        
        template<class Table>
        struct SetFreeOrMember<Table, false>
        {
            template<typename Func>
            static 
            void function(Table* table, const std::string& key, const Func func)
            {
                table->setFunction(key, func);
            }
        };
    }


    //****************************************************************************
    //        implemenation class Table
    //****************************************************************************

    template<class Host>
    Table<Host>::Table()
    {
    }

    template<class Host>
    Table<Host>::Table(lua_State* l) : Managed(l), Object(l), PlainTable(l)
    {
    }

    template<class Host>
    Table<Host>::Table(const PlainTable& rhs) : Managed(rhs.luaState()), Object(rhs.luaState()), PlainTable(rhs)
    {
        setMetatable(Typename<Host>::name());
    }

    template<class Host>
    Table<Host>::~Table()
    {}



    template<class Host>
    template<class Func>
    void Table<Host>::setMemberFunction(const std::string& key, const Func func)
    {
        if (key.empty())
            error("set<Host,Func>: error, key is empty");
        
        lua_State* L = luaState();

        // table[key] = value:                          // 
        push();                                         // t
        lua_pushstring        (L, key.c_str());         // t key
        ::nlua::push<Host>::memberFunction(L, func);    // t key value
        lua_rawset            (L, -3);                  // t
        pop();                                          //
    }


    template<class Host>
    Table<Host>::LhsReference::LhsReference(const std::string& k, Table* t) : key(k), table(t) 
    {
    }

    
    template<class Host>
    template<typename Func>
    Table<Host>& Table<Host>::LhsReference::operator=(const Func func) 
    {
        details::SetFreeOrMember<Table, std::tr1::is_member_function_pointer<Func>::value>::function(table, key, func);
        return *table;
    }


    template<class Host>
    Table<Host> &Table<Host>::LhsReference::operator=(const Table& t)
    { 
        table->setValue(key, t); 
        return *table; 
    }

        
    //****************************************************************************
    // Table<void>    
    //****************************************************************************

    template<>
    class Table<void> : public Object, public PlainTable
    {
    public:
        Table() : Managed(), Object(), PlainTable()  {}

        explicit Table(lua_State* state) : Managed(state), Object(state), PlainTable(state)
        {}

        Table(const PlainTable& t) : Managed(t.luaState()), Object(t.luaState()), PlainTable(t)
        {}

        virtual ~Table()
        {}
    };


    //****************************************************************************
    //         global push
    //****************************************************************************

    template<>
    struct push<Table<> >
    {
        static inline void value(lua_State* L, const PlainTable& table)
        {
            if( L!=table.luaState())
                error("void pushValue(lua_State*,const Object&): different lua states");
            table.push();
        }
    };

    template<class T>
    struct push<Table<T> >
    {
        static inline void value(lua_State* L, const Table<T>& table)
        {
            if( L!=table.luaState())
                error("void pushValue(lua_State*,const Object&): different lua states");
            table.push();
        }
    };

}

#endif
