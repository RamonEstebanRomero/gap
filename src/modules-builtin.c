/****************************************************************************
**
**  This file is part of GAP, a system for computational discrete algebra.
**
**  Copyright of GAP belongs to its developers, whose names are too numerous
**  to list here. Please refer to the COPYRIGHT file for details.
**
**  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "compiled.h"
#include "gap.h"
#include "hookintrprtr.h"
#include "intfuncs.h"
#include "iostream.h"
#include "objccoll.h"
#include "objset.h"
#include "profile.h"
#include "syntaxtree.h"
#include "vec8bit.h"
#include "vecffe.h"
#include "vecgf2.h"

#ifdef HPCGAP
#include "hpc/aobjects.h"
#include "hpc/serialize.h"
#include "hpc/threadapi.h"
#include "hpc/traverse.h"
#endif

extern StructInitInfo * InitInfoGap ( void );

/****************************************************************************
**
*V  InitFuncsBuiltinModules . . . . .  list of builtin modules init functions
*/
const InitInfoFunc InitFuncsBuiltinModules[] = {

#ifdef HPCGAP
    // Traversal functionality may be needed during the initialization
    // of some modules, so set it up as early as possible
    InitInfoTraverse,
#endif

    /* global variables                                                    */
    InitInfoGVars,

    /* objects                                                             */
    InitInfoObjects,

    /* profiling and interpreter hooking information */
    InitInfoProfile,
    InitInfoHookIntrprtr,

    /* scanner, reader, interpreter, coder, caller, compiler               */
    InitInfoIO,
    InitInfoScanner,
    InitInfoRead,
    InitInfoCalls,
    InitInfoExprs,
    InitInfoStats,
    InitInfoCode,
    InitInfoVars,       /* must come after InitExpr and InitStats */
    InitInfoFuncs,
    InitInfoOpers,
    InitInfoIntrprtr,
    InitInfoCompiler,

    /* arithmetic operations                                               */
    InitInfoAriths,
    InitInfoInt,
    InitInfoIntFuncs,
    InitInfoRat,
    InitInfoCyc,
    InitInfoFinfield,
    InitInfoPermutat,
    InitInfoTrans,
    InitInfoPPerm,
    InitInfoBool,
    InitInfoMacfloat,

    /* record packages                                                     */
    InitInfoRecords,
    InitInfoPRecord,

    /* list packages                                                       */
    InitInfoLists,
    InitInfoListOper,
    InitInfoListFunc,
    InitInfoPlist,
    InitInfoSet,
    InitInfoVector,
    InitInfoVecFFE,
    InitInfoBlist,
    InitInfoRange,
    InitInfoString,
    InitInfoGF2Vec,
    InitInfoVec8bit,

    /* free and presented groups                                           */
    InitInfoFreeGroupElements,
    InitInfoCosetTable,
    InitInfoTietze,
    InitInfoPcElements,
    InitInfoCollectors,
    InitInfoPcc,
    InitInfoDeepThought,
    InitInfoDTEvaluation,

    /* algebras                                                            */
    InitInfoSCTable,

    /* save and load workspace, weak pointers                              */
    InitInfoWeakPtr,
    InitInfoSaveLoad,

    /* syntax and parser tools */
    InitInfoSyntaxTree,

    /* input and output                                                    */
    InitInfoStreams,
    InitInfoSysFiles,
    InitInfoIOStream,

    /* main module                                                         */
    InitInfoModules,
    InitInfoGap,
    InitInfoError,

    // objsets / objmaps
    InitInfoObjSets,

#ifdef HPCGAP
    /* threads                                                             */
    InitInfoThreadAPI,
    InitInfoAObjects,
    InitInfoSerialize,
#endif

    0
};
