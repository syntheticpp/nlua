/****************************************************************************
* Copyright (C) 2011 Peter Kümmel
* All rights reserved.
*
* This file is part of the nlua and licensed under the licenses enlisted
* in the file COPYING included in the packaging of this file.
****************************************************************************/
#ifndef NLUA_GET_H
#define NLUA_GET_H

#include <nlua/match.h>
#include <nlua/boxeddata.h>

namespace nlua 
{
    namespace details 
    {

        //***********************************************************************
        //
        //            get
        //            - called indirect from lua (lua->bindcall->bind->pushcall->get)
        //            - gets the arguments from the stack 
        //
        //***********************************************************************


        inline char           getValue(TypeWrapper<char>          , lua_State* L, int idx){ return static_cast<char>          (lua_tonumber(L, idx)); }
        inline unsigned char  getValue(TypeWrapper<unsigned char> , lua_State* L, int idx){ return static_cast<unsigned char> (lua_tonumber(L, idx)); }
        inline short          getValue(TypeWrapper<short>         , lua_State* L, int idx){ return static_cast<short>         (lua_tonumber(L, idx)); }
        inline unsigned short getValue(TypeWrapper<unsigned short>, lua_State* L, int idx){ return static_cast<unsigned short>(lua_tonumber(L, idx)); }
        inline int            getValue(TypeWrapper<int>           , lua_State* L, int idx){ return static_cast<int>           (lua_tonumber(L, idx)); }
        inline unsigned int   getValue(TypeWrapper<unsigned int>  , lua_State* L, int idx){ return static_cast<unsigned int>  (lua_tonumber(L, idx)); }
        inline long           getValue(TypeWrapper<long>          , lua_State* L, int idx){ return static_cast<long>          (lua_tonumber(L, idx)); }
        inline unsigned long  getValue(TypeWrapper<unsigned long> , lua_State* L, int idx){ return static_cast<unsigned long> (lua_tonumber(L, idx)); }
        inline float          getValue(TypeWrapper<float>         , lua_State* L, int idx){ return static_cast<float>         (lua_tonumber(L, idx)); }
        inline double         getValue(TypeWrapper<double>        , lua_State* L, int idx){ return static_cast<double>        (lua_tonumber(L, idx)); }
        inline const char*    getValue(TypeWrapper<const char*>   , lua_State* L, int idx){ return static_cast<const char*>   (lua_tostring(L, idx)); }
        inline lua_CFunction  getValue(TypeWrapper<lua_CFunction> , lua_State* L, int idx){ return static_cast<lua_CFunction> (lua_tocfunction(L, idx)); }
        inline Nil            getValue(TypeWrapper<Nil>           , lua_State* L, int idx){ (void)L, (void)idx;  return Nil(); }
        inline bool           getValue(TypeWrapper<bool>          , lua_State* L, int idx){ return lua_toboolean(L, idx) != 0; }
        inline void           getValue(TypeWrapper<void>          , lua_State*  , int    ){ }

    }

    //*****************************************************************************
    //
    //        getcallee: gets pointer of the calling object (this) from the stack    
    //
    //*****************************************************************************

    
    template<class T>
    struct get
    {
        // use only the specialisations
    };


#define  NLUA_GET_VALUE(T)                                              \
                                                                        \
    template<>                                                          \
    struct get<T>                                                       \
    {                                                                   \
        static T value(lua_State* L, int index)                         \
        {                                                               \
            return details::getValue(TypeWrapper<T>(), L, index);    \
        }                                                               \
    }

    NLUA_GET_VALUE(bool);
    NLUA_GET_VALUE(char);
    NLUA_GET_VALUE(unsigned char);
    NLUA_GET_VALUE(short);
    NLUA_GET_VALUE(unsigned short);
    NLUA_GET_VALUE(int);
    NLUA_GET_VALUE(unsigned int);
    NLUA_GET_VALUE(long);
    NLUA_GET_VALUE(unsigned long);
    NLUA_GET_VALUE(double);
    NLUA_GET_VALUE(float);
    NLUA_GET_VALUE(const char*);


    template<class T>
    struct get<T*>
    {
        static T* functionPointer(lua_State* L, int index)
        {
            if (lua_type(L, index) != LUA_TUSERDATA) {
                luaL_argerror(L, 1, "nlua: must be userdata");
            }
            return static_cast<T*>(lua_touserdata(L, index));
        }
        
        static T* value(lua_State* L, int index)
        {
            return BoxedData<T>::address(L, index);
        }
    };

}


#endif

