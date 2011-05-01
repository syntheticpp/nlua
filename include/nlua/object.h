/****************************************************************************
* Copyright (C) 2011 Peter Kümmel
* All rights reserved.
*
* This file is part of the nlua and licensed under the licenses enlisted
* in the file COPYING included in the packaging of this file.
****************************************************************************/
#ifndef NLUA_OBJECT_H
#define NLUA_OBJECT_H

#include <nlua/managed.h>
#include <nlua/plaintable.h>


namespace  nlua
{

    //****************************************************************************
    //        class Object
    //****************************************************************************
    
    class NLUA_EXPORT Object : virtual public Managed
    {
    public:
       
        virtual ~Object();

        Object(const Object&);
        Object& operator=(const Object&);


        void pushValue(const std::string& key) const;
        void popValue(const std::string& key) const;

        void setValuesMetatable(const std::string& key, const std::string& mtname);
        void setValuesMetatable(const std::string& key, const PlainTable& mt);
        void setMetatable(const PlainTable& mt);
        void setMetatable(const std::string& name);

        PlainTable metatable() const;
        PlainTable metatableAuto();


    protected:
        Object();
        explicit Object(lua_State*);
        void registerObject(const int index);

    private:
        ObjectRegistry registry;
        int ref;
        bool isNil_;
        bool isObject(const int index) const;
    };


}



#endif
