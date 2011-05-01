/****************************************************************************
* Copyright (C) 2011 Peter Kümmel
* All rights reserved.
*
* This file is part of the nlua and licensed under the licenses enlisted
* in the file COPYING included in the packaging of this file.
****************************************************************************/
#ifndef NLUA_PUSHVALUE_H
#define NLUA_PUSHVALUE_H


#ifndef _MSC_VER
#include <tr1/type_traits>
#else
#include <type_traits>
#endif


namespace nlua 
{
    namespace details
    {
        inline void pushValue(lua_State* L, bool           v){  lua_pushboolean (L, static_cast<int>(v)); }
        inline void pushValue(lua_State* L, char           v){  lua_pushnumber  (L, static_cast<lua_Number>(v)); }
        inline void pushValue(lua_State* L, unsigned char  v){  lua_pushnumber  (L, static_cast<lua_Number>(v)); }
        inline void pushValue(lua_State* L, short          v){  lua_pushnumber  (L, static_cast<lua_Number>(v)); }
        inline void pushValue(lua_State* L, unsigned short v){  lua_pushnumber  (L, static_cast<lua_Number>(v)); }
        inline void pushValue(lua_State* L, int            v){  lua_pushnumber  (L, static_cast<lua_Number>(v)); }
        inline void pushValue(lua_State* L, unsigned int   v){  lua_pushnumber  (L, static_cast<lua_Number>(v)); }
        inline void pushValue(lua_State* L, long           v){  lua_pushnumber  (L, static_cast<lua_Number>(v)); }
        inline void pushValue(lua_State* L, unsigned long  v){  lua_pushnumber  (L, static_cast<lua_Number>(v)); }
        inline void pushValue(lua_State* L, double         v){  lua_pushnumber  (L, static_cast<lua_Number>(v)); }
        inline void pushValue(lua_State* L, float          v){  lua_pushnumber  (L, static_cast<lua_Number>(v)); }
        inline void pushValue(lua_State* L, const char*    v){  lua_pushstring  (L, v); }
        inline void pushValue(lua_State* L, const Nil&      ){  lua_pushnil     (L); }
    
    }


    template<class T>
    struct push; // use only the specialisations

    
    #define  NLUA_PUSH_VALUE(T)                                      \
                                                                     \
    template<>                                                       \
    struct push<T>                                                   \
    {                                                                \
        static void value(lua_State* L, T value)                     \
        {                                                            \
            return details::pushValue(L, value);                 \
        }                                                            \
    };


    NLUA_PUSH_VALUE(bool)                
    NLUA_PUSH_VALUE(char)            
    NLUA_PUSH_VALUE(unsigned char)        
    NLUA_PUSH_VALUE(short)            
    NLUA_PUSH_VALUE(unsigned short)    
    NLUA_PUSH_VALUE(int )                
    NLUA_PUSH_VALUE(unsigned int)        
    NLUA_PUSH_VALUE(long)                
    NLUA_PUSH_VALUE(unsigned long)        
    NLUA_PUSH_VALUE(double)        
    NLUA_PUSH_VALUE(float)                
    NLUA_PUSH_VALUE(const char*)    

    
}

#endif

