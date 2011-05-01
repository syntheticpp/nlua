/****************************************************************************
* Copyright (C) 2011 Peter Kümmel
* All rights reserved.
*
* This file is part of the nlua and licensed under the licenses enlisted
* in the file COPYING included in the packaging of this file.
****************************************************************************/
#ifndef NLUA_TYPE_NAME_H
#define NLUA_TYPE_NAME_H

#include <nlua/nlua.h>

#include <string>
#include <typeinfo>


namespace nlua
{

    inline const std::string typeNameToMetatableName(const std::string& tname)
	{
		const std::string mtname = tname + std::string(".Metatable");
		return mtname;
	}



    //****************************************************************************
    //        Type system
    //****************************************************************************

    template<class T>
    struct RttiTypename
    {
        static std::string get()
        {
            T* t = 0;
            return typeid(t).name();
        }
    };

    struct NLUA_EXPORT TypenameRegistry
    {
        TypenameRegistry();
        ~TypenameRegistry();

        static TypenameRegistry& instance();

        void insert(const std::string& key, const std::string& value);
        const std::string find(const std::string& key) const;

    private:
        struct Private;
        Private* d;
    };


    template<class T, template<class> class NamePolicy = RttiTypename>
    struct Typename
    {   
        static std::string  name();
        static void setName(lua_State* L, const std::string& type_name);
    };


    template<class T, template<class> class NamePolicy>
    void Typename<T, NamePolicy>::setName(lua_State* L, const std::string& type_name)
    {
        std::string name = type_name;
        if (name.empty()) {
            name = NamePolicy<T>::get();
        }
        TypenameRegistry::instance().insert(NamePolicy<T>::get(), name);
        luaL_newmetatable(L, name.c_str());
        lua_setmetatable(L, -2);
    }


    template<class T, template<class> class NamePolicy>
    std::string Typename<T, NamePolicy>::name()
    {
        return NamePolicy<T>::get();
    }

}


#endif
