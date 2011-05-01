/****************************************************************************
* Copyright (C) 2011 Peter Kümmel
* All rights reserved.
*
* This file is part of the nlua and licensed under the licenses enlisted
* in the file COPYING included in the packaging of this file.
****************************************************************************/
#ifndef NLUA_DETAILS_BIND_H
#define NLUA_DETAILS_BIND_H

#include <nlua/details/callpush.h>

namespace nlua {
namespace details {

    //***********************************************************************
    //
    //            bind
    //            - function which is called from bindcall with  
    //              pointers to object and arguments
    //
    //***********************************************************************




    //***********************************************************************
    //            member functions
    //***********************************************************************

    template<class Host = void>
    struct bind
    {
        template<typename R>
        static inline int function(Host& h, R (Host::* const func)(), lua_State* L, int arg1index)
        {
            return callpush<R>::run(h, func, L, arg1index);
        }

        template<typename R,    typename P1>
        static inline int function(Host& h, R (Host::* const func)(P1), lua_State* L, int arg1index)
        {
            return callpush<R>::run(h, func, L, arg1index);
        }

        template<typename R,    typename P1, 
                                typename P2>
        static inline int function(Host& h, R (Host::* const func)(P1, P2), lua_State* L, int arg1index)
        {
            return callpush<R>::run(h, func, L, arg1index);
        }

        template<typename R,    typename P1, 
                                typename P2, 
                                typename P3>
        static inline int function(Host& h, R (Host::* const func)(P1, P2, P3), lua_State* L, int arg1index)
        {
            return callpush<R>::run(h, func, L, arg1index);
        }


        //***********************************************************************
        //            const member functions
        //***********************************************************************
        
        template <typename R>
        static inline int function(const Host& h, R (Host::* const func)() const, lua_State* L, int arg1index)
        {
            return callpush<R>::run(h, func, L, arg1index);
        }

        template<typename R,    typename P1>
        static inline int function(const Host& h, R (Host::* const func)(P1) const, lua_State* L, int arg1index)
        {
            return callpush<R>::run(h, func, L, arg1index);
        }

        template<typename R,    typename P1, 
                                typename P2>
        static inline int function(const Host& h, R (Host::* const func)(P1, P2) const, lua_State* L, int arg1index)
        {
            return callpush<R>::run(h, func, L, arg1index);
        }

        template<typename R,    typename P1, 
                                typename P2, 
                                typename P3>
        static inline int function(const Host& h, R (Host::* const func)(P1, P2, P3) const, lua_State* L, int arg1index)
        {
            return callpush<R>::run(h, func, L, arg1index);
        }
    };


    //***********************************************************************
    //            free functions
    //***********************************************************************
        
    template<>
    struct bind<void>
    {
        template <typename R>
        static int function(R (* const func)(), lua_State* L, int arg1index)
        {
            return callpush<R>::run(func, L, arg1index);
        }

        template <typename R,    typename P1>
        static int function(R (* const func)(P1), lua_State* L, int arg1index)
        {
            return callpush<R>::run(func, L, arg1index);
        }

        template <typename R,    typename P1, 
                                typename P2>
        static int function(R (* const func)(P1, P2), lua_State* L, int arg1index)
        {
            return callpush<R>::run(func, L, arg1index);
        }

        template<typename R,    typename P1, 
                                typename P2, 
                                typename P3>
        static int function(R (* const func)(P1, P2, P3), lua_State* L, int arg1index)
        {
            return callpush<R>::run(func, L, arg1index);
        }
    };

}
}


#endif
