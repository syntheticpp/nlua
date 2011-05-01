/****************************************************************************
* Copyright (C) 2011 Peter Kümmel
* All rights reserved.
*
* This file is part of the nlua and licensed under the licenses enlisted
* in the file COPYING included in the packaging of this file.
****************************************************************************/
#include <nlua/engine.h>



namespace  nlua
{

    //****************************************************************************
    //        Engine
    //****************************************************************************

    Engine::Engine() : lua_state(0)
    {
        lua_state = lua_open();
        luaL_openlibs(lua_state);
    }


    Engine::Engine(lua_State* L) : lua_state(L)
    {
    }


    Engine::Engine(const Engine& rhs)
    {
        lua_state = rhs.lua_state;
    }


    Engine& Engine::operator=(const Engine& rhs) 
    {
        if(this!=&rhs)
            lua_state = rhs.lua_state;
        return *this;
    }


    Engine::~Engine()
    {
        lua_close(lua_state);
        lua_state = 0;
    }


    lua_State* Engine::luaState() const
    {
        if(lua_state==0) {
            error("Table::luaState() no valid lua_State.");
        }
            
        return lua_state;
    }


    bool Engine::doFile(const std::string& filename)
    {
        int error = luaL_dofile(lua_state, filename.c_str());
        if ( error != 0)
        {
            std::string msg("Error in lua script file ");
            msg += filename;
            //std::cout << msg << std::endl;
            //throw std::runtime_error( msg );
            return false;
        }
        return true;
    }


    bool Engine::doString(const std::string& string)
    {
        int error = luaL_dostring(lua_state, string.c_str());
        if ( error != 0)
        {
            //std::string msg("Error in lua string: ");
            //std::cout << msg << string << std::endl;
            //throw std::runtime_error( msg );
            printf("\nLua error:\n     %s\n\n", lua_tostring(lua_state, -1));
            return false;
        }
        return true;
    }


}

