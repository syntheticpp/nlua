/****************************************************************************
* Copyright (C) 2011 Peter Kümmel
* All rights reserved.
*
* This file is part of the nlua and licensed under the licenses enlisted
* in the file COPYING included in the packaging of this file.
****************************************************************************/
#ifndef NLUA_MANAGED_H
#define NLUA_MANAGED_H

#include <nlua/objectregistry.h>


namespace  nlua
{

    //****************************************************************************
    //        class Managed
    //****************************************************************************
   
    class NLUA_EXPORT Managed
    {
    public:
        Managed(const Managed&);
        Managed& operator=(const Managed&);

        virtual ~Managed();
        
        bool isNil() const;

        void setLuaState(lua_State*);
        lua_State* luaState() const;
        
        operator lua_State*() ;
        operator lua_State*() const ;

        void push() const;
        void pop() const;

        void unregister();

        void use();
        void use(int index);


    protected:
        Managed();
        Managed(lua_State*);
        void registerObject(const int index);

    private:        
        ObjectRegistry registry;
        int ref;
        bool isNil_;
        bool isObject(const int index) const;
    };

}



#endif
