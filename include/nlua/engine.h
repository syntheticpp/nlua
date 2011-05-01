/****************************************************************************
* Copyright (C) 2011 Peter Kümmel
* All rights reserved.
*
* This file is part of the nlua and licensed under the licenses enlisted
* in the file COPYING included in the packaging of this file.
****************************************************************************/
#ifndef NLUA_MASCHINE_H
#define NLUA_MASCHINE_H

#include <nlua/nlua_export.h>
#include <nlua/nlua.h>
#include <string>


namespace  nlua
{
    //****************************************************************************
    //        Engine
    //****************************************************************************

    class NLUA_EXPORT Engine
    {
    public:
        Engine();
        explicit Engine(lua_State*);
        explicit Engine(const Engine&);
        ~Engine();

        operator lua_State*() const { return luaState(); }
        lua_State* luaState() const;

        bool doString(const std::string&);
        bool doFile(const std::string&);

        Engine& operator=(const Engine&);

    private:
        lua_State* lua_state;
    };

}

#endif
