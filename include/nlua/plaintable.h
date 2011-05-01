/****************************************************************************
* Copyright (C) 2011 Peter Kümmel
* All rights reserved.
*
* This file is part of the nlua and licensed under the licenses enlisted
* in the file COPYING included in the packaging of this file.
****************************************************************************/
#ifndef NLUA_PAIN_TABLE_H
#define NLUA_PAIN_TABLE_H

#include <nlua/managed.h>

#include <nlua/push.h>
#include <nlua/pushvalue.h>




namespace  nlua
{

    template<class T>
    class Table;

    template<class T>
    class Userdata;


    //****************************************************************************
    //        class PlainTable
    //****************************************************************************
    
    class NLUA_EXPORT PlainTable : virtual public Managed
    {
    public:

        PlainTable(); 
        explicit PlainTable(lua_State*);

        PlainTable(const PlainTable&);
        PlainTable& operator=(const PlainTable&);

        virtual ~PlainTable();
        
        void create();


        PlainTable table(const int index) const;
        PlainTable table(const std::string& key) const;
        PlainTable tableAuto(const std::string& key);


        template<typename T>
        void setValue(const std::string& key, const T& value);

        void setClosure(const std::string& key, lua_CFunction f, int upvalues);

        template<typename Func>
        void setFunction(const std::string& key, const Func func);


        struct LhsReference
        {
            LhsReference(const std::string& k, PlainTable* t) : key(k), table(t) {}

            template<typename Func>
            PlainTable& operator=(const Func func) { table->setFunction(key, func); return *table; }
            
            PlainTable& operator=(const PlainTable& t) { table->setValue(key, t); return *table; }

            template<class T>
            PlainTable& operator=(const Table<T>& t) { table->setValue(key, t); return *table; }

            template<class T>
            PlainTable& operator=(const Userdata<T>& data) { table->setValue(key, data); return *table; }

        private:
            const std::string& key;
            PlainTable* table;
        };

        LhsReference operator[](const std::string& key) { return LhsReference(key, this); }
      
    };

    
    //****************************************************************************
    //        PlainTable template definitions
    //****************************************************************************

    template<typename T>
    void PlainTable::setValue(const std::string& key, const T& value)
    {            
        if (key.empty())
            error("settable: error, key is empty");

        lua_State* L = luaState();
        
        // table[key] = value:                      // 
        push();                                     // t
        lua_pushstring          (L, key.c_str());   // t key
        ::nlua::push<T>::value  (L, value);         // t key value
        lua_rawset              (L, -3);            // t
        pop();    
    }


    template<typename Func>
    void PlainTable::setFunction(const std::string& key, const Func func)
    {
        if (key.empty())
            error("settable: error, key is empty");

        lua_State* L = luaState();
        
        // table[key] = value:                     // 
        push();                                    // t
        lua_pushstring        (L, key.c_str());    // t key
        ::nlua::push<>::freeFunction(L, func);     // t key value
        lua_rawset            (L, -3);             // t
        pop();
    }

    //****************************************************************************
    //         global push
    //****************************************************************************

    template<>
    struct push<PlainTable>
    {
        static inline void value(lua_State* L, const PlainTable& table)
        {
            if( L!=table.luaState())
                error("void pushValue(lua_State*,const Object&): different lua states");
            table.push();
        }
    };

}



#endif
