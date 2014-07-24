//========= Copyright (c) 1996-2002, Valve LLC, All rights reserved. ==========
//
// Purpose:
//
// $NoKeywords: $
//=============================================================================

#ifndef PHYSICS_SAVERESTORE_H
#define PHYSICS_SAVERESTORE_H

#if defined( _WIN32 )
#pragma once
#endif

#include "vphysics_interface.h"

class ISaveRestoreBlockHandler;
class IPhysicsObject;
class CPhysCollide;

//-----------------------------------------------------------------------------

ISaveRestoreBlockHandler *GetPhysSaveRestoreBlockHandler();
ISaveRestoreOps *GetPhysObjSaveRestoreOps( PhysInterfaceId_t );

//-------------------------------------

#define DEFINE_PHYSPTR(type,name) \
	{ FIELD_CUSTOM, #name, { offsetof(type,name), 0 }, 1, FTYPEDESC_SAVE, NULL, GetPhysObjSaveRestoreOps( GetPhysIID( &(((type *)0)->name) ) ), NULL }

#define DEFINE_PHYSPTR_ARRAY(type,name) \
	{ FIELD_CUSTOM, #name, { offsetof(type,name), 0 }, ARRAYSIZE(((type *)0)->name), FTYPEDESC_SAVE, NULL, GetPhysObjSaveRestoreOps( GetPhysIID( &(((type *)0)->name[0]) ) ), NULL }

//-----------------------------------------------------------------------------

class IPhysSaveRestoreManager
{
public:
	virtual void NoteBBox( const Vector &mins, const Vector &maxs, CPhysCollide * ) = 0;

	virtual void AssociateModel( IPhysicsObject *, int modelIndex ) = 0;
	virtual void AssociateModel( IPhysicsObject *, const CPhysCollide *pModel ) = 0;
	virtual void ForgetModel( IPhysicsObject * ) = 0;

	virtual void ForgetAllModels() = 0;
};

extern IPhysSaveRestoreManager *g_pPhysSaveRestoreManager;

//=============================================================================

#endif // PHYSICS_SAVERESTORE_H
