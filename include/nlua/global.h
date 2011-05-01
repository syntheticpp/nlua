/****************************************************************************
* Copyright (C) 2011 Peter Kümmel
* All rights reserved.
*
* This file is part of the nlua and licensed under the licenses enlisted
* in the file COPYING included in the packaging of this file.
****************************************************************************/
#ifndef NLUA_GLOBAL_H
#define NLUA_GLOBAL_H

#include <nlua/table.h>
#include <nlua/engine.h>

#include <string>


namespace  nlua
{

    //****************************************************************************
    //        class Global
    //****************************************************************************

    class NLUA_EXPORT Global : public Table<>
    {
    public:
        explicit Global(const Engine&);
        explicit Global(lua_State*);
        virtual ~Global();

    private:
        Global();
        Global(const Global&);
        Global& operator=(const Global&);
        void init();
    };


}

#endif
