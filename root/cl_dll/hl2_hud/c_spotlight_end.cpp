//========= Copyright ? 1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "cbase.h"
#include "dlight.h"
#include "iefx.h"

//##################################################################
//
// PlasmaBeamNode - generates plasma embers
//
//##################################################################
class C_SpotlightEnd : public C_BaseEntity
{
public:
	DECLARE_CLASS( C_SpotlightEnd, C_BaseEntity );
	DECLARE_CLIENTCLASS();
	C_SpotlightEnd();

public:
	void	OnDataChanged(DataUpdateType_t updateType);
	bool	ShouldDraw();
	void	ClientThink( void );

	Vector	m_vSpotlightOrg;
	Vector	m_vSpotlightDir;
	float	m_flLightScale;
	float	m_Radius;

private:
	dlight_t*	m_pDynamicLight;
	dlight_t*	m_pModelLight;
};

//------------------------------------------------------------------------------
// Purpose :
// Input   :
// Output  :
//------------------------------------------------------------------------------
C_SpotlightEnd::C_SpotlightEnd(void) : m_pModelLight(0), m_pDynamicLight(0)
{
	m_flLightScale	= 100;
}

//------------------------------------------------------------------------------
// Purpose :
// Input   :
// Output  :
//------------------------------------------------------------------------------
void C_SpotlightEnd::OnDataChanged(DataUpdateType_t updateType)
{
	if ( updateType == DATA_UPDATE_CREATED )
	{
		SetNextClientThink(gpGlobals->curtime + 0.05);
	}
}

//------------------------------------------------------------------------------
// Purpose :
// Input   :
// Output  :
//------------------------------------------------------------------------------
bool C_SpotlightEnd::ShouldDraw()
{
	return false;
}

//------------------------------------------------------------------------------
// Purpose :
// Input   :
// Output  :
//------------------------------------------------------------------------------
void C_SpotlightEnd::ClientThink(void)
{
	// If light scale is zero, don't draw light
	if (m_flLightScale <= 0)
	{
		return;
	}

	// Deal with the environment light
	if ( !m_pDynamicLight || (m_pDynamicLight->key != index) )
	{
		m_pDynamicLight = effects->CL_AllocDlight( index );
		assert (m_pDynamicLight);
	}

	m_pDynamicLight->flags = DLIGHT_NO_MODEL_ILLUMINATION;
	m_pDynamicLight->radius		= m_flLightScale;
	m_pDynamicLight->origin		= GetAbsOrigin()+Vector(0,0,5);
	m_pDynamicLight->die		= gpGlobals->curtime + 0.05;
	m_pDynamicLight->color.r	= m_clrRender->r * m_clrRender->a;
	m_pDynamicLight->color.g	= m_clrRender->g * m_clrRender->a;
	m_pDynamicLight->color.b	= m_clrRender->b * m_clrRender->a;
	m_pDynamicLight->color.exponent	= 5;

	// For bumped lighting
	VectorCopy (m_vSpotlightDir,  m_pDynamicLight->m_Direction);

	// Deal with the model light
 	if ( !m_pModelLight || (m_pModelLight->key != -index) )
	{
		m_pModelLight = effects->CL_AllocDlight( -index );
		assert (m_pModelLight);
	}

	m_pModelLight->radius = m_Radius;
	m_pModelLight->flags = DLIGHT_NO_WORLD_ILLUMINATION;
	m_pModelLight->color.r = m_clrRender->r * m_clrRender->a;
	m_pModelLight->color.g = m_clrRender->g * m_clrRender->a;
	m_pModelLight->color.b = m_clrRender->b * m_clrRender->a;
	m_pModelLight->color.exponent	= 5;
	m_pModelLight->origin		= m_vSpotlightOrg;
	m_pModelLight->m_InnerAngle = 6;
	m_pModelLight->m_OuterAngle = 8;
	m_pModelLight->die = gpGlobals->curtime + 0.05;
	VectorCopy( m_vSpotlightDir, m_pModelLight->m_Direction );

	SetNextClientThink(gpGlobals->curtime + 0.05);
}

IMPLEMENT_CLIENTCLASS_DT(C_SpotlightEnd, DT_SpotlightEnd, CSpotlightEnd)
	RecvPropFloat	(RECVINFO(m_flLightScale)),
	RecvPropFloat	(RECVINFO(m_Radius)),
	RecvPropVector	(RECVINFO(m_vSpotlightOrg)),
	RecvPropVector	(RECVINFO(m_vSpotlightDir)),
END_RECV_TABLE()
