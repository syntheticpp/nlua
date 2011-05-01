/****************************************************************************
* Copyright (C) 2011 Peter Kümmel
* All rights reserved.
*
* This file is part of the nlua and licensed under the licenses enlisted
* in the file COPYING included in the packaging of this file.
****************************************************************************/
#include <nlua/nlua.h>
#include <nlua/typename.h>




namespace  nlua
{


    //****************************************************************************
    //        error function
    //****************************************************************************


    void argument_error(lua_State* L, int index)
    {
        luaL_argerror(L, index, "bad argument");
    }


    void error(const char * str) 
    {
        error(std::string(str));
    }


    void error(const std::string msg) 
    {
        throw namespaceluaexep();
    }

    
    namespaceluaexep::namespaceluaexep() : exception()
    {
    }


    const char* namespaceluaexep::what() const throw()
    {
        return "error in namespace nlua ";
    }


}

