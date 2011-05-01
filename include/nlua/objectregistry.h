/****************************************************************************
* Copyright (C) 2011 Peter Kümmel
* All rights reserved.
*
* This file is part of the nlua and licensed under the licenses enlisted
* in the file COPYING included in the packaging of this file.
****************************************************************************/
#ifndef NLUA_OBJECTREGISTRY_H
#define NLUA_OBJECTREGISTRY_H

#include <nlua/nlua.h>


#include <string>


namespace  nlua
{
    class Managed;

    //****************************************************************************
    //        class ObjectRegistry
    //****************************************************************************

    class NLUA_EXPORT ObjectRegistry
    {
    public:
        ObjectRegistry();
        ~ObjectRegistry();
        
        ObjectRegistry& operator=(const ObjectRegistry&);

        void init(lua_State*);

        void setLuaState(lua_State*);
        lua_State* luaState() const;

        void unregisterObject(const Managed &);
        int registerObject(int index);    

        void push() const;
        void pop() const;    

    private:
        lua_State* state;
        int luareference;
    };


}



#endif
