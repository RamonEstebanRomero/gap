/****************************************************************************
**
**  This file is part of GAP, a system for computational discrete algebra.
**
**  Copyright of GAP belongs to its developers, whose names are too numerous
**  to list here. Please refer to the COPYRIGHT file for details.
**
**  SPDX-License-Identifier: GPL-2.0-or-later
**
**  This file declares the functions handling Info statements.
*/


#include "info.h"

#include "bool.h"
#include "calls.h"
#include "gvars.h"
#include "modules.h"
#include "plist.h"

#ifdef HPCGAP
#include "hpc/aobjects.h"
#endif

enum {
    INFODATA_NUM = 1,
    INFODATA_CURRENTLEVEL,
    INFODATA_CLASSNAME,
    INFODATA_HANDLER,
    INFODATA_OUTPUT,
};

static Obj InfoDecision;
static Obj IsInfoClassListRep;
static Obj DefaultInfoHandler;

void InfoDoPrint(Obj cls, Obj lvl, Obj args)
{
    if (IS_PLIST(cls))
        cls = ELM_PLIST(cls, 1);
#if defined(HPCGAP)
    Obj fun = Elm0AList(cls, INFODATA_HANDLER);
#else
    Obj fun = ELM_PLIST(cls, INFODATA_HANDLER);
#endif
    if (!fun)
        fun = DefaultInfoHandler;

    CALL_3ARGS(fun, cls, lvl, args);
}


Obj InfoCheckLevel(Obj selectors, Obj level)
{
    // Fast-path the most common failing case.
    // The fast-path only deals with the case where all arguments are of the
    // correct type, and were False is returned.
    if (CALL_1ARGS(IsInfoClassListRep, selectors) == True) {
#if defined(HPCGAP)
        Obj index = ElmAList(selectors, INFODATA_CURRENTLEVEL);
#else
        Obj index = ELM_PLIST(selectors, INFODATA_CURRENTLEVEL);
#endif
        if (IS_INTOBJ(index) && IS_INTOBJ(level)) {
            // < on INTOBJs compares the represented integers.
            if (index < level) {
                return False;
            }
        }
    }
    return CALL_2ARGS(InfoDecision, selectors, level);
}

/****************************************************************************
**
*F * * * * * * * * * * * * * initialize module * * * * * * * * * * * * * * *
*/


/****************************************************************************
**
*F  InitKernel( <module> )  . . . . . . . . initialise kernel data structures
*/
static Int InitKernel(StructInitInfo * module)
{
    /* The work of handling Info messages is delegated to the GAP level */
    ImportFuncFromLibrary("InfoDecision", &InfoDecision);
    ImportFuncFromLibrary("DefaultInfoHandler", &DefaultInfoHandler);
    ImportFuncFromLibrary("IsInfoClassListRep", &IsInfoClassListRep);

    /* return success                                                      */
    return 0;
}


/****************************************************************************
**
*F  InitLibrary( <module> ) . . . . . . .  initialise library data structures
*/
static Int InitLibrary(StructInitInfo * module)
{
    ExportAsConstantGVar(INFODATA_CURRENTLEVEL);
    ExportAsConstantGVar(INFODATA_CLASSNAME);
    ExportAsConstantGVar(INFODATA_HANDLER);
    ExportAsConstantGVar(INFODATA_OUTPUT);
    ExportAsConstantGVar(INFODATA_NUM);

    /* return success                                                      */
    return 0;
}

/****************************************************************************
**
*F  InitInfoInfo()  . . . . . . . . . . . . . . . . . table of init functions
*/
static StructInitInfo module = {
    // init struct using C99 designated initializers; for a full list of
    // fields, please refer to the definition of StructInitInfo
    .type = MODULE_BUILTIN,
    .name = "info",
    .initKernel = InitKernel,
    .initLibrary = InitLibrary,
};

StructInitInfo * InitInfoInfo(void)
{
    return &module;
}