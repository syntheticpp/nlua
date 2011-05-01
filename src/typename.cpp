/****************************************************************************
* Copyright (C) 2011 Peter Kümmel
* All rights reserved.
*
* This file is part of the nlua and licensed under the licenses enlisted
* in the file COPYING included in the packaging of this file.
****************************************************************************/
#include <nlua/typename.h>
#include <nlua/metatable.h>

#include <map>


namespace nlua
{

    struct TypenameRegistry::Private
    {
        std::map<std::string, std::string> map;
    };


    TypenameRegistry::TypenameRegistry() : d(new Private)
    {
        d->map.clear();
    }

    TypenameRegistry::~TypenameRegistry()
    {
        delete d;
    }

    void TypenameRegistry::insert(const std::string& key, const std::string& value)
    {
        d->map[key] = value;
    }

    const std::string TypenameRegistry::find(const std::string& key) const
    {
        return d->map[key];
    }


    TypenameRegistry& TypenameRegistry::instance()
    {
        static TypenameRegistry reg;
        return reg;
    }
    
}

