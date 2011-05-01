/****************************************************************************
* Copyright (C) 2011 Peter Kümmel
* All rights reserved.
*
* This file is part of the nlua and licensed under the licenses enlisted
* in the file COPYING included in the packaging of this file.
****************************************************************************/
#include <nlua/global.h>

namespace nlua
{

    //****************************************************************************
    //        class Global
    //****************************************************************************
    
    Global::Global(lua_State* s) : Managed(s), Table<>(s)
    {
        init();
    }


    Global::Global(const Engine& m) : Managed(m.luaState()), Table<>(m.luaState())
    {
        init();
    }


    void Global::init()
    {
                                                            //
        lua_pushvalue(luaState(), LUA_GLOBALSINDEX);        // globaltable
        use();                                              //
    }


    Global::~Global()
    {
    }


}

