/****************************************************************************
* Copyright (C) 2011 Peter Kümmel
* All rights reserved.
*
* This file is part of the nlua and licensed under the licenses enlisted
* in the file COPYING included in the packaging of this file.
****************************************************************************/
#ifndef NLUA_DISPATCHER_H
#define NLUA_DISPATCHER_H


#include <nlua/details/cclosure.h>

namespace nlua
{
    
    //*********************************************************************************
    //
    //        push (member) function on stack
    //            
    //        called from C/C++ to push functions and member functions on the stack
    //        pointer to (member)function is the first upvalue
    //        when calling lua_pushcclosure there is only ONE upvalue on the stack
    //
    //*********************************************************************************
    
    //*********************************************************************************
    //            member functions
    //          and functions on members
    //*********************************************************************************
    template<class Host = void>
    struct push
    {

        //*********************************************************************************
        //            member functions
        //*********************************************************************************

        template<typename Func>
        static inline void memberFunction(lua_State* L, const Func func) 
        {
            Func* f = static_cast<Func*>(lua_newuserdata(L, sizeof(Func)));
            *f = func;
            lua_pushcclosure(L, details::cclosure<Host>::template callMemberFunction<Func, 2>, 1);
        }

        static inline void memberFunction(lua_State* L, int (Host::* const func)(lua_State*))
        {
            typedef int (Host::* Func)(lua_State*);
            Func* f = static_cast<Func*>(lua_newuserdata(L, sizeof(Func)));
            *f = func;
            ::lua_pushcclosure(L, details::cclosure<Host>::callMemberFunction, 1);
        }

        static inline void memberFunction(lua_State* L, int (Host::* const func)(lua_State*) const)
        {
            typedef int (Host::* Func)(lua_State*) const ;
            Func* f = static_cast<Func*>(lua_newuserdata(L, sizeof(Func)));
            *f = func;
            ::lua_pushcclosure(L, details::cclosure<Host>::callMemberFunction, 1);
        }

    };


    //*********************************************************************************
    //            free functions
    //*********************************************************************************
    
    template<>
    struct push<void>
    {
        template<typename Func>
        static inline void freeFunction(lua_State* L, const Func func)
        {
            Func* f = static_cast<Func*>(lua_newuserdata(L, sizeof(Func)));
            *f = func;
            ::lua_pushcclosure(L, details::cclosure<>::callFreeFunction<Func, 1>, 1);
        }

        // special case for lua_CFunction, the lua_State is not a real argument
        static inline void freeFunction(lua_State* L, lua_CFunction f)
        {  
            lua_pushcclosure(L, f, 0);
        }
    };

}




#endif 



/*
>         -- I want to write code like this
>         v = new( "Vector" );
>         v:SetNull();
>         v.x = 0.2;      -- for now, i must write:       v.x:Parse( CreateString( "0.2" ) );
>         v.y = 1.5;      -- for now, i must write:       v.y:Parse( CreateString( "1.5" ) );
>
>         -- i need to hook to the assignment operation in order to correctly set
> v.x.

Just use the __newindex metamethod. It could look like this:

function __newindex(u, k, v)
 local class = getmetatable(u)
 local mutator = class.mutators[k]
 if mutator then
   mutator(u, v)
 else
   error(string.format("missing mutator %s in class %s", tostring(k),
tostring(class)), 2)
 end
end 
*/
