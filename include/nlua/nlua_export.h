/****************************************************************************
* Copyright (C) 2011 Peter Kümmel
* All rights reserved.
*
* This file is part of the nlua and licensed under the licenses enlisted
* in the file COPYING included in the packaging of this file.
****************************************************************************/
#ifndef NLUA_NLUA_EXPORT_H
#define NLUA_NLUA_EXPORT_H

#if (defined(NLUA_MAKE_DLL) && defined(NLUA_DLL)) || \
    (defined(NLUA_MAKE_DLL) && defined(NLUA_STATIC)) || \
    (defined(NLUA_DLL) && defined(NLUA_STATIC))
#error export macro error: you could not build AND use the library
#endif

#ifdef NLUA_MAKE_DLL
#define NLUA_EXPORT __declspec(dllexport)
#endif

#ifdef NLUA_DLL
#define NLUA_EXPORT __declspec(dllimport)
#endif

#ifdef NLUA_STATIC
#define NLUA_EXPORT
#endif

#if !defined(NLUA_EXPORT) && !defined(NLUA_EXPLICIT_EXPORT)
#define NLUA_EXPORT
#endif

#ifndef NLUA_EXPORT
#error export macro error: NLUA_EXPORT was not defined, disable NLUA_EXPLICIT_EXPORT or define a export specification
#endif


#endif 
