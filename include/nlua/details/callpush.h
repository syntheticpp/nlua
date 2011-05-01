/****************************************************************************
* Copyright (C) 2011 Peter Kümmel
* All rights reserved.
*
* This file is part of the nlua and licensed under the licenses enlisted
* in the file COPYING included in the packaging of this file.
****************************************************************************/
#ifndef NLUA_DETAILS_CALLPUSH_H
#define NLUA_DETAILS_CALLPUSH_H

#include <nlua/getvalue.h>
#include <nlua/pushvalue.h>
#include <nlua/match.h>

namespace nlua {
namespace details {


//***********************************************************************
//
//            callpush
//            - called  from lua->bindcall->bind->callpush
//            - unpacks the arguments and calls C/C++ function and 
//            pushes the return value on the stack
//
//***********************************************************************

template<typename R>
struct callpush
{
        
    //***********************************************************************
    //            free functions
    //***********************************************************************
    
    template <typename P1>
    static int run(R (* const func)(P1), lua_State* L, int index)
    {
        luaL_argassert(1, index + 0);
        R r = func(
            get<P1>::value(L, index + 0)
        );
        push<R>::value(L, r);
        return 1;
    }

    
    //***********************************************************************
    //            member functions
    //***********************************************************************
    
    template <class Host, typename P1>
    static int run(Host& h, R (Host::* const func)(P1), lua_State* L, int index)
    {
        luaL_argassert(1, index + 0);
        R r = (h.*func)(
            get<P1>::value(L, index + 0)
        );
        push<R>::value(L, r);
        return 1;
    }




    //***********************************************************************
    //
    //            callpush repetitions 
    //            in:
    //                template<typename R>
    //                struct callpush
    //
    //***********************************************************************


    //***********************************************************************
    //            free functions
    //***********************************************************************


    static int run(R (* const func)()
                    , lua_State* L, int /*index*/)
    {
        R r = func();
        push<R>::value(L, r);
        return 1;
    }

    template <typename P1, typename P2>
    static int run(R (* const func)(P1, P2)
                    , lua_State* L, int index)
    {
        luaL_argassert(1, index + 0);
        luaL_argassert(2, index + 1);
        R r = func(
            get<P1>::value(L, index + 0),
            get<P2>::value(L, index + 1)
        );
        push<R>::value(L, r);
        return 1;
    }

    template <typename P1, typename P2, typename P3>
    static int run(R (* const func)(P1, P2, P3)
                    , lua_State* L, int index)
    {
        luaL_argassert(1, index + 0);
        luaL_argassert(2, index + 1);
        luaL_argassert(3, index + 2);
        R r = func(
            get<P1>::value(L, index + 0),
            get<P2>::value(L, index + 1),
            get<P2>::value(L, index + 2)
        );
        push<R>::value(L, r);
        return 1;
    }


    //***********************************************************************
    //            member functions
    //***********************************************************************

    template <class Host>
    static int run(Host& h, R (Host::* const func)()
                    , lua_State* L, int /*index*/)
    {
        R r = (h.*func)();
        push<R>::value(L, r);
        return 1;
    }

    template <class Host, typename P1, typename P2>
    static int run(Host& h, R (Host::* const func)(P1,P2)
                    , lua_State* L, int index)
    {
        luaL_argassert(1, index + 0);
        luaL_argassert(2, index + 1);
        R r = (h.*func)(
            get<P1>::value(L, index + 0),
            get<P2>::value(L, index + 1)
        );
        push<R>::value(L, r);
        return 1;
    }

    template <class Host, typename P1, typename P2, typename P3>
    static int run(Host& h, R (Host::* const func)(P1,P2,P3)
                    , lua_State* L, int index)
    {
        luaL_argassert(1, index + 0);
        luaL_argassert(2, index + 1);
        luaL_argassert(3, index + 2);
        R r = (h.*func)(
            get<P1>::value(L, index + 0),
            get<P2>::value(L, index + 1),
            get<P3>::value(L, index + 2)
        );
        push<R>::value(L, r);
        return 1;
    }

    //***********************************************************************
    //            const member functions
    //***********************************************************************

    template <class Host>
    static int run(const Host& h, R (Host::* const func)() const, lua_State* L, int /*index*/)
    {
        R r = (h.*func)();
        push<R>::value(L, r);
        return 1;
    }

    template <class Host, typename P1>
    static int run(const Host& h, R (Host::* const func)(P1) const, lua_State* L, int index)
    {
        luaL_argassert(1, index + 0);
        R r = (h.*func)(
            get<P1>::value(L, index + 0)
        );
        push<R>::value(L, r);
        return 1;
    }

    template <class Host,    typename P1, 
                            typename P2>
    static int run(const Host& h, R (Host::* const func)(P1,P2) const, lua_State* L, int index)
    {
        luaL_argassert(1, index + 0);
        luaL_argassert(2, index + 1);
        R r = (h.*func)(
            get<P1>::value(L, index + 0),
            get<P2>::value(L, index + 1)
        );
        push<R>::value(L, r);
        return 1;
    }

    template <class Host,    typename P1, 
                            typename P2, 
                            typename P3>
    static int run(const Host& h, R (Host::* const func)(P1,P2,P3) const, lua_State* L, int index)
    {
        luaL_argassert(1, index + 0);
        luaL_argassert(2, index + 1);
        luaL_argassert(3, index + 2);
        R r = (h.*func)(
            get<P1>::value(L, index + 0),
            get<P2>::value(L, index + 1),
            get<P3>::value(L, index + 2)
        );
        push<R>::value(L, r);
        return 1;
    }



};    // template<typename R>
// struct callpush



    //***********************************************************************
    //
    //            callpush void specialisation        
    //
    //***********************************************************************

template<>
struct callpush<void>
{

    //***********************************************************************
    //            free functions
    //***********************************************************************

    static int run(void (* const func)()
                    , lua_State* L, int /*index*/)
    {
        (void)L;
        func();
        return 1;
    }

    template <typename P1>
    static int run(void (* const func)(P1)
                    , lua_State* L, int index)
    {
        luaL_argassert(1, index + 0);
        func(
            get<P1>::value(L, index + 0)
        );
        return 1;
    }
            
    template<typename P1, typename P2>
    static int run(void (* const func)(P1, P2)
                    , lua_State* L, int index)
    {
        luaL_argassert(1, index + 0);
        luaL_argassert(2, index + 1);
        func(
            get<P1>::value(L, index + 0),
            get<P2>::value(L, index + 1)
        );
        return 1;
    }

    template <typename P1, typename P2, typename P3>
    static int run(void (* const func)(P1, P2, P3)
                    , lua_State* L, int index)
    {
        luaL_argassert(1, index + 0);
        luaL_argassert(2, index + 1);
        luaL_argassert(3, index + 2);
        func(
            get<P1>::value(L, index + 0),
            get<P2>::value(L, index + 1),
            get<P3>::value(L, index + 2)
        );
        return 1;
    }

    //***********************************************************************
    //             member functions
    //***********************************************************************

    template <class Host>
    static int run(Host& h, void (Host::* const func)()
                    , lua_State* /*L*/, int /*index*/)
    {
        (h.*func)();
        return 1;
    }


    template <class Host, typename P1>
    static int run(Host& h, void (Host::* const func)(P1)
                    , lua_State* L, int index)
    {
        luaL_argassert(1, index + 0);
        (h.*func)(
            get<P1>::value(L, index + 0)
        );
        return 1;
    }

    template <class Host, typename P1, typename P2>
    static int run(Host& h, void (Host::* const func)(P1,P2)
                    , lua_State* L, int index)
    {
        luaL_argassert(1, index + 0);
        luaL_argassert(2, index + 1);
        (h.*func)(
            get<P1>::value(L, index + 0),
            get<P2>::value(L, index + 1)
        );
        return 1;
    }
                
    template <class Host, typename P1, typename P2, typename P3>
    static int run(Host& h, void (Host::* const func)(P1,P2,P3)
                    , lua_State* L, int index)
    {
        luaL_argassert(1, index + 0);
        luaL_argassert(2, index + 1);
        luaL_argassert(3, index + 2);
        (h.*func)(
            get<P1>::value(L, index + 0),
            get<P2>::value(L, index + 1),
            get<P3>::value(L, index + 2)
        );
        return 1;
    }

    //***********************************************************************
    //            const member functions
    //***********************************************************************

    template <class Host>
    static int run(const Host& h, void (Host::* const func)() const, lua_State* /*L*/, int /*index*/)
    {
        (h.*func)();
        return 1;
    }


    template <class Host,    typename P1>
    static int run(const Host& h, void (Host::* const func)(P1) const, lua_State* L, int index)
    {
        luaL_argassert(1, index + 0);
        (h.*func)(
            get<P1>::value(L, index + 0)
        );
        return 1;
    }

    template <class Host,    typename P1, 
                            typename P2>
    static int run(const Host& h, void (Host::* const func)(P1,P2) const, lua_State* L, int index)
    {
        luaL_argassert(1, index + 0);
        (h.*func)(
            get<P1>::value(L, index + 0),
            get<P2>::value(L, index + 1)
        );
        return 1;
    }
                
    template <class Host,    typename P1, 
                            typename P2, 
                            typename P3>
    static int run(const Host& h, void (Host::* const func)(P1,P2,P3) const, lua_State* L, int index)
    {
        luaL_argassert(1, index + 0);
        luaL_argassert(2, index + 1);
        luaL_argassert(3, index + 2);
        (h.*func)(
            get<P1>::value(L, index + 0),
            get<P2>::value(L, index + 1),
            get<P3>::value(L, index + 2)
        );
        return 1;
    }

};    



}
}

#endif
