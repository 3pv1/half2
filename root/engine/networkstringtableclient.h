//========= Copyright ? 1996-2001, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#ifndef NETWORKSTRINGTABLECLIENT_H
#define NETWORKSTRINGTABLECLIENT_H
#ifdef _WIN32
#pragma once
#endif

class CUtlBuffer;

void CL_ParseStringTables( void );
void CL_ParseUpdateStringTable( void );
void CL_PrintStringTables( void );
void CL_WriteStringTables( CUtlBuffer& buf );
bool CL_ReadStringTables( CUtlBuffer& buf );

#endif // NETWORKSTRINGTABLECLIENT_H
