/****************************************************************************
* Copyright (C) 2011 Peter Kümmel
* All rights reserved.
*
* This file is part of the nlua and licensed under the licenses enlisted
* in the file COPYING included in the packaging of this file.
****************************************************************************/

#ifndef NLUA_H
#define NLUA_H

#ifdef NLUA_LUA_COMPILED_AS_C
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}
#else
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#endif


#include <nlua/nlua_export.h>

#include <string>



namespace  nlua
{


    //****************************************************************************
    //        error function
    //****************************************************************************

    void NLUA_EXPORT error(const char *);
    void NLUA_EXPORT error(const std::string msg);

    
    struct NLUA_EXPORT namespaceluaexep : public std::exception
    {
        namespaceluaexep();
        const char* what() const throw();
    };

    void NLUA_EXPORT argument_error(lua_State* L, int index);
        
        
    struct Nil
    {};


}

#endif
