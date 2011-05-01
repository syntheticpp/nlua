/****************************************************************************
* Copyright (C) 2011 Peter Kümmel
* All rights reserved.
*
* This file is part of the nlua and licensed under the licenses enlisted
* in the file COPYING included in the packaging of this file.
****************************************************************************/
#ifndef LUA_MATCH_H
#define LUA_MATCH_H

namespace nlua {

    template<class T> 
    struct TypeWrapper 
    {};


    template<class T>
    inline bool    match(TypeWrapper<T>             , lua_State* L, int idx){ return lua_isuserdata(L, idx)!=0; }

    inline bool    match(TypeWrapper<bool>          , lua_State* L, int idx){ return lua_type(L, idx) == LUA_TBOOLEAN; }
    inline bool    match(TypeWrapper<char>          , lua_State* L, int idx){ return lua_type(L, idx) == LUA_TNUMBER; }
    inline bool    match(TypeWrapper<unsigned char> , lua_State* L, int idx){ return lua_type(L, idx) == LUA_TNUMBER; }
    inline bool    match(TypeWrapper<short>         , lua_State* L, int idx){ return lua_type(L, idx) == LUA_TNUMBER; }
    inline bool    match(TypeWrapper<unsigned short>, lua_State* L, int idx){ return lua_type(L, idx) == LUA_TNUMBER; }
    inline bool    match(TypeWrapper<int>           , lua_State* L, int idx){ return lua_type(L, idx) == LUA_TNUMBER; }
    inline bool    match(TypeWrapper<unsigned int>  , lua_State* L, int idx){ return lua_type(L, idx) == LUA_TNUMBER; }
    inline bool    match(TypeWrapper<long>          , lua_State* L, int idx){ return lua_type(L, idx) == LUA_TNUMBER; }
    inline bool    match(TypeWrapper<unsigned long> , lua_State* L, int idx){ return lua_type(L, idx) == LUA_TNUMBER; }
    inline bool    match(TypeWrapper<float>         , lua_State* L, int idx){ return lua_type(L, idx) == LUA_TNUMBER; }
    inline bool    match(TypeWrapper<double>        , lua_State* L, int idx){ return lua_type(L, idx) == LUA_TNUMBER; }
    inline bool    match(TypeWrapper<const char*>   , lua_State* L, int idx){ return lua_type(L, idx) == LUA_TSTRING; }



    // TODO rename
#define luaL_argassert(arg, _index_)                            \
            if (!match(TypeWrapper<P##arg>(), L, _index_))      \
                argument_error(L, _index_)       
}


#endif

