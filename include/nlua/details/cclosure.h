/****************************************************************************
* Copyright (C) 2011 Peter Kümmel
* All rights reserved.
*
* This file is part of the nlua and licensed under the licenses enlisted
* in the file COPYING included in the packaging of this file.
****************************************************************************/
#ifndef NLUA_DETAILS_CCLOSURE_H
#define NLUA_DETAILS_CCLOSURE_H

#include <nlua/details/bind.h>
#include <nlua/boxeddata.h>


namespace nlua {
namespace details 
{

    //****************************************************************************
    //
    //        cclosure         
    //        - function which is registerd in lua
    //        - function which is is direct called from lua
    //        - gets pointer to the arguments from the stack
    //
    //****************************************************************************

    template<class Host = void> 
    struct cclosure
    {

        //***********************************************************************
        //            calling member functions
        //***********************************************************************
        
        static inline int callMemberFunction(lua_State* L)
        {
            typedef int (Host::*Func)(lua_State*);
            Host& h = *BoxedData<Host>::address(L, 1);
            Func f = *get<Func*>::functionPointer(L, lua_upvalueindex(1));
            return (h.*f)(L);
        }

        template <typename Func, int arg1index>
        static inline int callMemberFunction(lua_State* L)
         {
            // userdata created by Lua:     T*
            // pointers stored in a userdata T**
            Host& h = *BoxedData<Host>::address(L, 1);
            Func f = *get<Func*>::functionPointer(L, lua_upvalueindex(1));
            return bind<Host>::function(h, f, L, arg1index);
        }

    };

    //***********************************************************************
    //            calling free functions
    //***********************************************************************
    
    template<> 
    struct cclosure<void>
    {
        template <typename Func, int arg1index>
        static inline int callFreeFunction(lua_State* L)
        {
            Func f = *get<Func*>::functionPointer(L, lua_upvalueindex(1));
            return bind<>::function(f, L, arg1index);
        }
    };


}
} 


#endif
