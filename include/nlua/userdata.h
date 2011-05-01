/****************************************************************************
* Copyright (C) 2011 Peter Kümmel
* All rights reserved.
*
* This file is part of the nlua and licensed under the licenses enlisted
* in the file COPYING included in the packaging of this file.
****************************************************************************/
#ifndef NLUA_USERDATA_H
#define NLUA_USERDATA_H

#include <nlua/object.h>


namespace  nlua
{
   
    //****************************************************************************
    //        class Userdata
    //****************************************************************************

    template<class T>
    class Userdata : public Object
    {
    public:    

        Userdata();
        virtual ~Userdata();
        
        explicit Userdata(lua_State*);
        Userdata(lua_State*, int index);

        void setData(T*);
        void create(size_t addBytes = 0);
        
        typedef void (*Destructor)(T*);
        Destructor destructor() const;
        
        T* data() const;

    private:
        T* ptr;
    };



    //****************************************************************************
    //        Implemenation 
    //****************************************************************************

    template<class T>
    Userdata<T>::Userdata() : Object()
    {
    }


    template<class T>
    Userdata<T>::Userdata(lua_State* s) : Managed(s), Object(s)
    {        
    }


    template<class T>
    Userdata<T>::Userdata(lua_State* s, int index) : Managed(s), Object(s)
    {
        use(index);
    }


    template<class T>
    Userdata<T>::~Userdata()
    {
    }


    template<class T>
    void Userdata<T>::create(size_t add_bytes)
    {    
        unregister();
        BoxedData<T>::create(*this, add_bytes);
        use();
    }


    template<class T>
    typename Userdata<T>::Destructor Userdata<T>::destructor() const
    {
        return BoxedData<T>::destruct;
    }

    template<class T>
    void Userdata<T>::setData(T* cdata) 
    {
        unregister();
        BoxedData<T>::wrap(*this, cdata);
        use();
    }


    template<class T>
    T* Userdata<T>::data() const
    {    
        Managed::push();
        T* ptr = BoxedData<T>::address(*this, -1);
        Managed::pop();
        return ptr;
    }



    //****************************************************************************
    //         global push
    //****************************************************************************

    template<class T>
    struct push<Userdata<T> >
    {
        static inline void value(lua_State* L, const Userdata<T>& userdata)
        {
            if( L!=userdata.luaState()) {
                error("void pushValue(lua_State*,const Object&): different lua states");
            }
            userdata.push();
        }
    };


}


#endif
