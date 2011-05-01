/****************************************************************************
* Copyright (C) 2011 Peter Kümmel
* All rights reserved.
*
* This file is part of the nlua and licensed under the licenses enlisted
* in the file COPYING included in the packaging of this file.
****************************************************************************/
#ifndef NLUA_BOXED_DATA_H
#define NLUA_BOXED_DATA_H

#include <nlua/nlua.h>
#include <nlua/typename.h>


namespace nlua
{


    /*
    *  Data which is filled by Lua's lua_newuserdata
    */

    template<class T, class D>
    struct Box
    {
        T* ptr;
        D data;  // size of data could change at runtime, ptr must be before data
    };


    template<class T>
    struct Box<T, void>
    {
        T* ptr;
    };


    /*
    * From and to Lua
    */
    template<class T>
    struct BoxedData
    {
        static T* address(lua_State* L, int index);
        static T* create(lua_State* L, size_t add_bytes, const std::string& type_name = std::string());     
        static void destruct(T* t);
        static void wrap(lua_State* L, T* cdata, const std::string& type_name = std::string());
    };
   


    template<class T>
    T* BoxedData<T>::create(lua_State* L, size_t add_bytes, const std::string& type_name)
    {
        int size = sizeof(Box<T, T>) + add_bytes;
        Box<T, T>* box = static_cast<Box<T, T>*>(lua_newuserdata(L, size));
        box->ptr = &box->data;
        new(box->ptr) T();

        Typename<T>::setName(L, type_name);

        return box->ptr;
    }


    template<class T>
    void BoxedData<T>::destruct(T* t) 
    { 
        t->~T(); 
    }


    template<class T>
    void BoxedData<T>::wrap(lua_State* L, T* cdata, const std::string& type_name)
    {      
        int size = sizeof(Box<T, void>);
        Box<T, void>* box = static_cast<Box<T, void>*>(lua_newuserdata(L, size));
        box->ptr = cdata;

        Typename<T>::setName(L, type_name);
    }



    template<class T>
    T* BoxedData<T>::address(lua_State* L, int index)
    {
        const std::string type_name = TypenameRegistry::instance().find(Typename<T>::name());
        void* ud = luaL_checkudata(L, index, type_name.c_str());
        luaL_argcheck(L, ud != NULL, index, std::string("'" + type_name + "' expected").c_str());
        Box<T, void>* box = static_cast<Box<T, void>*>(ud);
        return box->ptr;
    }



}


#endif
